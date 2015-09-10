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
		// delete
		QSqlQuery query(*m_pDB);
		query.prepare("DELETE FROM directories WHERE path = :path");
		query.bindValue(":path", listRemove.at(i));
		query.exec();

		// todo remove scan jobs

		// todo remove all indexed files from db
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
    
    for (int i = 0; i < listRemove.size(); i++) {
		// start scan
		QSqlQuery query(*m_pDB);
		query.prepare("UPDATE directories SET lastscanning = CURRENT_TIMESTAMP WHERE path = :path");
		query.bindValue(":path", listRemove.at(i));
		query.exec();
		// todo start job
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
				  "size varchar(20), "
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
	{
		QHBoxLayout *pHLayout = new QHBoxLayout();
		m_pLineEditSearch = new QLineEdit();
		connect(m_pLineEditSearch, SIGNAL(returnPressed()), this, SLOT(btnFilesSearch()));
		pHLayout->addWidget(m_pLineEditSearch);
		
		QPushButton *pBtnSearch = new QPushButton("Search...");
		pBtnSearch->setMaximumWidth(100);
		connect(pBtnSearch, SIGNAL(clicked()), this, SLOT(btnFilesSearch()));
		pHLayout->addWidget(pBtnSearch);

		QWidget *pWidget = new QWidget;
		pWidget->setLayout(pHLayout);
		pFilesLayout->addWidget(pWidget);
	}
	
	{
		m_pLabelResult = new QLabel();
		m_pLabelResult->setText("No filters...");
		pFilesLayout->addWidget(m_pLabelResult);
	}

	m_pTableView_Files = new QTableView();
	m_pFilesModel = new FilesModel(m_pDB);
	m_pTableView_Files->setModel( m_pFilesModel );
	pFilesLayout->addWidget(m_pTableView_Files);
	m_pFilesWidget->setLayout(pFilesLayout);
}

// ---------------------------------------------------------------------

void MainWindow::btnFilesSearch() {
	QString sTextSearch = m_pLineEditSearch->displayText();
	m_pFilesModel->setSearchText(sTextSearch);

	int nFound = m_pFilesModel->foundRecords();

	if (sTextSearch == "")
		m_pLabelResult->setText("No filters... Records found: " + QString::number(nFound));
	else {
		m_pLabelResult->setText("Filter '" + sTextSearch.toHtmlEscaped() + "', Records found:  " + QString::number(nFound));
	}

	QMessageBox msgBox;
	msgBox.setText("Todo");
	msgBox.exec();
}

// ---------------------------------------------------------------------

void MainWindow::initJobsTabs() {
	m_pJobsWidget = new QWidget();
}
