#include "mainwindow.h"
#include <QWheelEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDebug>
#include <QFileInfo>
#include <qmath.h>
#include <iostream>
#include <QApplication>
#include <QDir>
#include <QIcon>
#include <QFileDialog>
#include "detection/detection.h"
#include "scandialog.h"

MainWindow::MainWindow(QString sWorkDirectory) : 
 m_appIcon(QIcon(":/res/inventory-files.png")) {
    m_pTrayIcon = new QSystemTrayIcon(this);

    // Read version
    QFile fileVersion(":/VERSION");
    if (fileVersion.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&fileVersion);
        while (!stream.atEnd()) {
            m_sVersionApp.append(stream.readLine()+"\n");
        }
    }
    fileVersion.close();
    m_sVersionApp = m_sVersionApp.trimmed();

    m_sWorkDirectory = sWorkDirectory;
    setWindowTitle("Inventory-files (" + m_sVersionApp + ")");
    setMinimumSize(1000, 600);
    setWindowIcon(m_appIcon);
    initConnection();
    initActions();

    // Tray icon menu
    initTrayIcon();

    // menu
    {
        m_pMenuFile = menuBar()->addMenu("&File");
        m_pMenuHelp = menuBar()->addMenu("&Help");
        m_pMenuHelp->addAction(m_pActionAbout);
    }
    
    m_pTabWidget = new QTabWidget();

    // directory tabs
    initDirectoryTabs();
    m_pTabWidget->addTab(m_pDirectoryWidget, "Directory for scanning...");
    
    // files tab
    initFilesTabs();
    m_pTabWidget->addTab(m_pFilesWidget, "Files");

    // jobs
    initJobsTabs();
    m_pTabWidget->addTab(m_pJobsWidget, "Jobs");

    // Main Layout
    m_pMainLayout = new QVBoxLayout();
    m_pMainLayout->addWidget(m_pTabWidget);
    
    setCentralWidget(m_pTabWidget);
}

// ---------------------------------------------------------------------

void MainWindow::showSystemMessage(QString sTitle, QString sMessage) {
    this->m_pTrayIcon->showMessage(sTitle, sMessage);
}

// ---------------------------------------------------------------------

void MainWindow::initTrayIcon() {
    // App can exit via Quit menu
    QAction *pQuitAction = new QAction("&Quit", this);
    connect(pQuitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    QMenu *pMenu = new QMenu(this);
    pMenu->addAction(pQuitAction);

    this->m_pTrayIcon->setIcon(m_appIcon);
    this->m_pTrayIcon->setContextMenu(pMenu);

    // Displaying the tray icon
    this->m_pTrayIcon->show();

    // Interaction
    connect(m_pTrayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
}

// ---------------------------------------------------------------------

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason_) {
  switch (reason_) {
  case QSystemTrayIcon::Trigger:
    this->m_pTrayIcon->showMessage("Hello", "You clicked me!");
    break;
  default:
    ;
  }
}

// ---------------------------------------------------------------------

void MainWindow::initActions(){
    m_pActionAbout = new QAction(tr("&About"), this);
    // newAct->setShortcuts(QKeySequence::New);
    m_pActionAbout->setStatusTip("About");
    connect(m_pActionAbout, SIGNAL(triggered()), this, SLOT(actionAbout()));

}

// ---------------------------------------------------------------------

void MainWindow::actionAbout() {
    // Read license
    QFile fileLicense(":/LICENSE");
    QString sFileLicenseContent;
    if (fileLicense.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&fileLicense);
        while (!stream.atEnd()) {
            sFileLicenseContent.append(stream.readLine()+"\n");
        }
    }
    fileLicense.close();
    sFileLicenseContent.replace("\n","<br>");

    // prepare and show dialog
    QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel{min-width: 700px;}");
    msgBox.setModal( true );
    msgBox.setWindowTitle("About");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(
        "<h2>inventory-files</h2> <br>"
        "Version: " + m_sVersionApp + " <br>"
        "Web-site: <a href='https://sea-kg.com/inventory-files/'>https://sea-kg.com/inventory-files/</a> <br>"
        "Source-code: <a href='https://github.com/sea-kg/inventory-files/'>https://github.com/sea-kg/inventory-files/</a> <br>"
        "<hr/>"
        "Author(s):<ul>"
        "  <li>Evgenii Sopov (mrseakg@gmail.com) </li>"
        "</ul><hr>"
        + sFileLicenseContent
    );
    msgBox.exec();
}

// ---------------------------------------------------------------------

void MainWindow::btnInsertDirectory() {
     QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
         "/home",
         QFileDialog::ShowDirsOnly
         | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        // check 
        {
            QSqlQuery query(*m_pDB);
            query.prepare("SELECT count(*) as cnt FROM directories WHERE path = :path");
            query.bindValue(":path", dir);
            query.exec();
            int nResult = 0;
            if (query.next()) {
                nResult = query.value(0).toInt();
            }
            
            if (nResult >= 1) {
                QMessageBox msgBox;
                msgBox.setText("This directory already exists");
                msgBox.exec();
                return;
            }
        }

        // insert
        {
            QSqlQuery query(*m_pDB);
            query.prepare("INSERT INTO directories(path) VALUES(:path)");
            query.bindValue(":path", dir);
            query.exec();
            m_pDirectoryModel->needReset();
        }
    }
}

// ---------------------------------------------------------------------

void MainWindow::btnRemoveDirectory() {
    // Get all selections
    QStringList listRemove;
    QModelIndexList indexes = m_pTableView_Directories->selectionModel()->selection().indexes();
    for (int i = 0; i < indexes.count(); ++i) {
        QModelIndex index = indexes.at(i);
        index = index.sibling(index.row(), 0);
        if (!listRemove.contains(index.data().toString()))
            listRemove << index.data().toString();
    }

    for (int i = 0; i < listRemove.size(); i++) {
        QString sPath = listRemove.at(i);

        m_pJobsModel->terminateJob(sPath);
        // delete from dirs
        {
            QSqlQuery query(*m_pDB);
            query.prepare("DELETE FROM directories WHERE path = :path");
            query.bindValue(":path", sPath);
            query.exec();
        }
        
        // delete from files
        {
            QSqlQuery query(*m_pDB);
            query.prepare("DELETE FROM files WHERE path LIKE :path");
            query.bindValue(":path", sPath + "%");
            query.exec();
        }
        m_pDirectoryModel->needReset();
    }
}

// ---------------------------------------------------------------------

void MainWindow::btnScanDirectory() {

    // Get all selections
    QStringList listRemove;
    QModelIndexList indexes = m_pTableView_Directories->selectionModel()->selection().indexes();
    for (int i = 0; i < indexes.count(); ++i) {
        QModelIndex index = indexes.at(i);
        index = index.sibling(index.row(), 0);
        if (!listRemove.contains(index.data().toString()))
            listRemove << index.data().toString();
    }
    QString strPaths = listRemove.join("\n");
    ScanDialog sd(this, strPaths);
    sd.setModal(true);
    if (sd.exec() == QDialog::Accepted){
        QStringList strListFilter = sd.filter();
        
        std::cout << "Filter not work now: " << strListFilter.join(", ").toStdString() << "\n";
        
        // return;
        for (int i = 0; i < listRemove.size(); i++) {
            QString sPath = listRemove.at(i);
            
            // start scan
            QSqlQuery query(*m_pDB);
            query.prepare("UPDATE directories SET lastscanning = CURRENT_TIMESTAMP WHERE path = :path");
            query.bindValue(":path", sPath);
            query.exec();

            m_pJobsModel->terminateJob(sPath);
            m_pJobsModel->runJob(sPath, this);
            m_pDirectoryModel->needReset();
        }
    }
}

// ---------------------------------------------------------------------        

void MainWindow::initConnection() {
    m_pDB = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    m_pDB->setDatabaseName(m_sWorkDirectory + "/db.sqlite");
    if (!m_pDB->open()) {
        std::cout << "Could not open database\n";
    }

    if (!m_pDB->tables().contains("directories")) {
        std::cout << "Table 'directories' did not exists\n";
        QSqlQuery query(*m_pDB);
        query.exec("create table directories "
                  "(id integer primary key, "
                  "path varchar(1024), "
                  "lastscanning datetime)");
    }

    if (!m_pDB->tables().contains("files")) {
        std::cout << "Table 'files' did not exists\n";
        QSqlQuery query(*m_pDB);
        query.exec("create table files "
                  "(id integer primary key, "
                  "path varchar(1024), "
                  "path_upper varchar(1024), "
                  "name varchar(255), "
                  "name_upper varchar(255), "
                  "md5 varchar(255), "
                  "comment varchar(1024), "
                  "comment_upper varchar(1024), "
                  "ext varchar(20), "
                  "type varchar(20), "
                  "size integer, "
                  "lastscanning datetime)");
    }
}

// ---------------------------------------------------------------------        

void MainWindow::initDirectoryTabs() {
    m_pDirectoryWidget = new QWidget();
    QVBoxLayout *pDirectoryLayout = new QVBoxLayout(m_pDirectoryWidget);
    m_pTableView_Directories = new QTableView();
    m_pDirectoryModel = new DirectoryModel(m_pDB);
    m_pTableView_Directories->setModel( m_pDirectoryModel );
    m_pTableView_Directories->setColumnWidth(0, 280);
    m_pTableView_Directories->setColumnWidth(1, 160);
    {
        QHBoxLayout *pHLayout = new QHBoxLayout();
        QPushButton *pBtnInsertDirectory = new QPushButton("Insert");
        pBtnInsertDirectory->setMaximumWidth(100);
        connect(pBtnInsertDirectory, SIGNAL(clicked()), this, SLOT(btnInsertDirectory()));
        pHLayout->addWidget(pBtnInsertDirectory);

        QPushButton *pBtnRemoveDirectory = new QPushButton("Remove");
        pBtnRemoveDirectory->setMaximumWidth(100);
        connect(pBtnRemoveDirectory, SIGNAL(clicked()), this, SLOT(btnRemoveDirectory()));
        pHLayout->addWidget(pBtnRemoveDirectory);

        QPushButton *pBtnScanDirectory = new QPushButton("Scan");
        pBtnScanDirectory->setMaximumWidth(100);
        connect(pBtnScanDirectory, SIGNAL(clicked()), this, SLOT(btnScanDirectory()));
        pHLayout->addWidget(pBtnScanDirectory);
        
        // empty space
        pHLayout->addWidget(new QWidget);

        QWidget *pWidget = new QWidget;
        pWidget->setLayout(pHLayout);
        pDirectoryLayout->addWidget(pWidget);
    }
    pDirectoryLayout->addWidget(m_pTableView_Directories);
    m_pDirectoryWidget->setLayout(pDirectoryLayout);
}

// ---------------------------------------------------------------------

void MainWindow::initFilesTabs() {
    m_pFilesWidget = new QWidget();
    QVBoxLayout *pFilesLayout = new QVBoxLayout(m_pFilesWidget);
    int nMinimumWidth = 100;

    // name like
    {
        QHBoxLayout *pHLayout = new QHBoxLayout();
        QLabel *pLabel = new QLabel("Name LIKE ");
        pLabel->setMinimumWidth(nMinimumWidth);
        pHLayout->addWidget(pLabel);

        m_pLineEditNameLike = new QLineEdit();
        connect(m_pLineEditNameLike, SIGNAL(returnPressed()), this, SLOT(btnFilesSearch()));
        pHLayout->addWidget(m_pLineEditNameLike);

        QWidget *pWidget = new QWidget;
        pWidget->setLayout(pHLayout);
        pFilesLayout->addWidget(pWidget);
    }
    
    // ext
    {
        QHBoxLayout *pHLayout = new QHBoxLayout();
        QLabel *pLabel = new QLabel("Ext = ");
        pLabel->setMinimumWidth(nMinimumWidth);
        pLabel->setMaximumWidth(nMinimumWidth);
        pHLayout->addWidget(pLabel);

        m_pLineEditExt = new QLineEdit();
        m_pLineEditExt->setMinimumWidth(100);
        m_pLineEditExt->setMaximumWidth(100);
        connect(m_pLineEditExt, SIGNAL(returnPressed()), this, SLOT(btnFilesSearch()));
        pHLayout->addWidget(m_pLineEditExt);

        pHLayout->addWidget(new QWidget);
        QWidget *pWidget = new QWidget;
        pWidget->setLayout(pHLayout);
        pFilesLayout->addWidget(pWidget);
    }

    // type file
    {
        QHBoxLayout *pHLayout = new QHBoxLayout();
        QLabel *pLabel = new QLabel("Type = ");
        pLabel->setMinimumWidth(nMinimumWidth);
        pLabel->setMaximumWidth(nMinimumWidth);
        pHLayout->addWidget(pLabel);

        m_pComboBox = new QComboBox();
        m_pComboBox->addItem("*");
        
        {
            Detection *pDetection = new Detection();
            QStringList ft;
            pDetection->types(ft);
            for (int i = 0; i < ft.size(); i++) {
                m_pComboBox->addItem(ft.at(i));
            }
        }
        pHLayout->addWidget(m_pComboBox);

        pHLayout->addWidget(new QWidget);
        QWidget *pWidget = new QWidget;
        pWidget->setLayout(pHLayout);
        pFilesLayout->addWidget(pWidget);
    }

    // size
    {
        QHBoxLayout *pHLayout = new QHBoxLayout();
        QLabel *pLabel = new QLabel("Size");
        pLabel->setMinimumWidth(nMinimumWidth);
        pLabel->setMaximumWidth(nMinimumWidth);
        pHLayout->addWidget(pLabel);

        m_pComboBoxSize = new QComboBox();
        m_pComboBoxSize->setMinimumWidth(50);
        m_pComboBoxSize->setMaximumWidth(50);
        m_pComboBoxSize->addItem("");
        m_pComboBoxSize->addItem(">");
        m_pComboBoxSize->addItem("<");
        m_pComboBoxSize->addItem("=");
        pHLayout->addWidget(m_pComboBoxSize);

        m_pLineEditSize = new QLineEdit();
        m_pLineEditSize->setMinimumWidth(50);
        m_pLineEditSize->setMaximumWidth(50);
        connect(m_pLineEditSize, SIGNAL(returnPressed()), this, SLOT(btnFilesSearch()));
        pHLayout->addWidget(m_pLineEditSize);

        pHLayout->addWidget(new QWidget);
        QWidget *pWidget = new QWidget;
        pWidget->setLayout(pHLayout);
        pFilesLayout->addWidget(pWidget);
    }
    
    // path like
    {
        QHBoxLayout *pHLayout = new QHBoxLayout();
        QLabel *pLabel = new QLabel("Path LIKE ");
        pLabel->setMinimumWidth(nMinimumWidth);
        pHLayout->addWidget(pLabel);

        m_pLineEditPathLike = new QLineEdit();
        connect(m_pLineEditPathLike, SIGNAL(returnPressed()), this, SLOT(btnFilesSearch()));
        pHLayout->addWidget(m_pLineEditPathLike);

        QWidget *pWidget = new QWidget;
        pWidget->setLayout(pHLayout);
        pFilesLayout->addWidget(pWidget);
    }

    // Comment
    {
        QHBoxLayout *pHLayout = new QHBoxLayout();
        QLabel *pLabel = new QLabel("Comment LIKE ");
        pLabel->setMinimumWidth(nMinimumWidth);
        pLabel->setMaximumWidth(nMinimumWidth);
        pHLayout->addWidget(pLabel);

        m_pLineEditComment = new QLineEdit();
        connect(m_pLineEditComment, SIGNAL(returnPressed()), this, SLOT(btnFilesSearch()));
        pHLayout->addWidget(m_pLineEditComment);

        pHLayout->addWidget(new QWidget);
        QWidget *pWidget = new QWidget;
        pWidget->setLayout(pHLayout);
        pFilesLayout->addWidget(pWidget);
    }

    // search button
    {
        QHBoxLayout *pHLayout = new QHBoxLayout();
        QPushButton *pBtnSearch = new QPushButton("Search...");
        pBtnSearch->setMaximumWidth(100);
        connect(pBtnSearch, SIGNAL(clicked()), this, SLOT(btnFilesSearch()));
        pHLayout->addWidget(pBtnSearch);

        pHLayout->addWidget(new QWidget);
        QWidget *pWidget = new QWidget;
        pWidget->setLayout(pHLayout);
        pFilesLayout->addWidget(pWidget);
    }

    m_pTableView_Files = new QTableView();
    m_pFilesModel = new QSqlQueryModel;
    // m_pFilesModel->setQuery("SELECT name, ext, type, size, path, comment, md5, lastscanning  FROM files");
    m_pFilesModel->setQuery("SELECT name, ext, type, size, path, lastscanning  FROM files");
    m_pFilesModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
    m_pFilesModel->setHeaderData(1, Qt::Horizontal, tr("Ext"));
    m_pFilesModel->setHeaderData(2, Qt::Horizontal, tr("Type"));
    m_pFilesModel->setHeaderData(3, Qt::Horizontal, tr("Size (In Bytes)"));
    m_pFilesModel->setHeaderData(4, Qt::Horizontal, tr("Path"));
    // m_pFilesModel->setHeaderData(5, Qt::Horizontal, tr("Comment"));
    // m_pFilesModel->setHeaderData(6, Qt::Horizontal, tr("md5sum"));
    m_pFilesModel->setHeaderData(7, Qt::Horizontal, tr("Last Scanning"));

    m_pTableView_Files->setModel( m_pFilesModel );
    pFilesLayout->addWidget(m_pTableView_Files);
    m_pFilesWidget->setLayout(pFilesLayout);
}

// ---------------------------------------------------------------------

void MainWindow::btnFilesSearch() {

    QStringList listQuery; 
    if (m_pLineEditNameLike->displayText() != "") {
        listQuery << "name_upper LIKE '%" + m_pLineEditNameLike->displayText().toUpper() + "%'";
    }

    if (m_pLineEditPathLike->displayText() != "") {
        listQuery << "path_upper LIKE '%" + m_pLineEditPathLike->displayText().toUpper() + "%'";
    }

    QString sType = m_pComboBox->itemText(m_pComboBox->currentIndex());
    if ( sType != "*") {
        listQuery << "type = '" + sType + "'";
    }
    
    int nSize = m_pLineEditSize->displayText().toInt();
    QString sSize = m_pComboBoxSize->itemText(m_pComboBoxSize->currentIndex());
    if (sSize != "") {
        listQuery << "size " + sSize + " " + QString::number(nSize);
    }

    QString sComment = m_pLineEditComment->displayText();
    if (sComment != "") {
        listQuery << "comment_upper LIKE '%" + sComment.toUpper() + "%'";
    }

    QString sExt = m_pLineEditExt->displayText();
    if (sExt != "") {
        listQuery << "ext = '" + sExt.toUpper() + "'";
    }

    QString where = "";
    if (listQuery.size() > 0) {
        where = where + " WHERE " + listQuery.join(" AND ");
    }
    // std::cout << where.toStdString() << "\n";

//  m_pFilesModel->setQuery("SELECT name, ext, type, size, path, comment, md5, lastscanning  FROM files " + where);
    m_pFilesModel->setQuery("SELECT name, ext, type, size, path, lastscanning  FROM files " + where);
}

// ---------------------------------------------------------------------

void MainWindow::initJobsTabs() {
    m_pJobsWidget = new QWidget();
    QVBoxLayout *pJobsLayout = new QVBoxLayout();
    
    m_pTableView_Jobs = new QTableView(m_pJobsWidget);
    m_pJobsModel = new JobsModel(m_pDB);

    m_pTableView_Jobs->setModel( m_pJobsModel );
    m_pTableView_Jobs->setColumnWidth(0, 400);
    m_pTableView_Jobs->setColumnWidth(1, 160);
    m_pTableView_Jobs->setColumnWidth(2, 160);
    
    pJobsLayout->addWidget(m_pTableView_Jobs);
    m_pJobsWidget->setLayout(pJobsLayout);
}

