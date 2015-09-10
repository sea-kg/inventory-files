#include "mainwindow.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QFileInfo>
#include <qmath.h>
#include <iostream>
#include <QApplication>
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QString sWorkDirectory)
{
	m_sWorkDirectory = sWorkDirectory;
    setWindowTitle("Inventory-files");
    setMinimumSize(1000, 600);

	initConnection();

    // actions
    {
		m_pActionLicense = new QAction(tr("&License"), this);
		// newAct->setShortcuts(QKeySequence::New);
		m_pActionLicense->setStatusTip("License");
		connect(m_pActionLicense, SIGNAL(triggered()), this, SLOT(actionLicense()));
	}

    // menu
    {
		m_pMenuHelp = menuBar()->addMenu("&Help");
		m_pMenuHelp->addAction(m_pActionLicense);
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

void MainWindow::actionLicense() {
	QMessageBox msgBox;
	msgBox.setText(
		"The MIT License (MIT)\n\n"
		"Copyright (c) 2015 Evgenii Sopov\n\n"
		"Permission is hereby granted, free of charge, to any person obtaining a copy"
		"of this software and associated documentation files (the \"Software\"), to deal"
		"in the Software without restriction, including without limitation the rights"
		"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell"
		"copies of the Software, and to permit persons to whom the Software is"
		"furnished to do so, subject to the following conditions:\n\n"
		"The above copyright notice and this permission notice shall be included in all"
		"copies or substantial portions of the Software.\n\n"
		"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR"
		"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,"
		"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE"
		"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER"
		"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,"
		"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE"
		"SOFTWARE."	
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
		
		terminateJob(sPath);
	
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

void MainWindow::terminateJob(QString sPath) {
	if (m_mapJobs.contains(sPath)) {
		if (m_mapJobs[sPath]->isFinished()) {
			std::cout << " job finished\n";
			m_mapJobs.remove(sPath);
			std::cout << "removed job.\n";
		} else {
			std::cout << "stopping job...\n";
			Job *pJob = m_mapJobs[sPath];
			pJob->terminate();
			while (!pJob->isFinished()) {
				std::cout << "stopping job...\n";
			}
			m_mapJobs.remove(sPath);
			std::cout << "removed job.\n";
		}
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
    
    for (int i = 0; i < listRemove.size(); i++) {
		QString sPath = listRemove.at(i);
		
		// start scan
		QSqlQuery query(*m_pDB);
		query.prepare("UPDATE directories SET lastscanning = CURRENT_TIMESTAMP WHERE path = :path");
		query.bindValue(":path", sPath);
		query.exec();
		
		terminateJob(sPath);
			
		Job *pJob = new Job(m_pDB, sPath);
		if (!m_mapJobs.contains(sPath)) {
			m_mapJobs[sPath] = pJob;
			pJob->start();
		} else {
			std::cout << " job already exists\n";
		}
		m_pDirectoryModel->needReset();
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
				  "name varchar(255), "
				  "md5 varchar(255), "
				  "comment varchar(1024), "
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
		m_pComboBox->addItem("Unknown");
		m_pComboBox->addItem("Source Code");
		m_pComboBox->addItem("Virtual Machine");
		m_pComboBox->addItem("Gimp");
		m_pComboBox->addItem("Images");
		m_pComboBox->addItem("Document");
		m_pComboBox->addItem("Text");
		m_pComboBox->addItem("Binary");
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
    m_pFilesModel->setQuery("SELECT name, ext, type, size, path, comment, md5, lastscanning  FROM files");
    m_pFilesModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
    m_pFilesModel->setHeaderData(1, Qt::Horizontal, tr("Ext"));
    m_pFilesModel->setHeaderData(2, Qt::Horizontal, tr("Type"));
    m_pFilesModel->setHeaderData(3, Qt::Horizontal, tr("Size (In Bytes)"));
    m_pFilesModel->setHeaderData(4, Qt::Horizontal, tr("Path"));
    m_pFilesModel->setHeaderData(5, Qt::Horizontal, tr("Comment"));
	m_pFilesModel->setHeaderData(6, Qt::Horizontal, tr("md5sum"));
	m_pFilesModel->setHeaderData(7, Qt::Horizontal, tr("Last Scanning"));
    
	m_pTableView_Files->setModel( m_pFilesModel );
	pFilesLayout->addWidget(m_pTableView_Files);
	m_pFilesWidget->setLayout(pFilesLayout);
}

// ---------------------------------------------------------------------

void MainWindow::btnFilesSearch() {

	QStringList listQuery; 
	if (m_pLineEditNameLike->displayText() != "") {
		listQuery << "name LIKE '%" + m_pLineEditNameLike->displayText() + "%'";
	}

	if (m_pLineEditPathLike->displayText() != "") {
		listQuery << "path LIKE '%" + m_pLineEditPathLike->displayText() + "%'";
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
		listQuery << "comment LIKE '%" + sComment + "%'";
	}

	QString sExt = m_pLineEditExt->displayText();
	if (sExt != "") {
		listQuery << "ext = '" + sExt.toUpper() + "'";
	}

	QString where = "";
	if (listQuery.size() > 0) {
		where = where + " WHERE " + listQuery.join(" OR ");
	}
	// std::cout << where.toStdString() << "\n";
	
	m_pFilesModel->setQuery("SELECT name, ext, type, size, path, comment, md5, lastscanning  FROM files " + where);
}

// ---------------------------------------------------------------------

void MainWindow::initJobsTabs() {
	m_pJobsWidget = new QWidget();
}
