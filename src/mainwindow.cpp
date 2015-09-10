#include "mainwindow.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QFileInfo>
#include <qmath.h>
#include <iostream>
#include <QApplication>
#include <QDir>

MainWindow::MainWindow()
{
    setWindowTitle("Inventory-files");
    setMinimumSize(500, 400);

	// work directory
	QDir dir(QDir::homePath());
	{
		if (!dir.exists(".inventory-files")) {
			if (!dir.mkdir(".inventory-files")) {
				dir.cd(".inventory-files");
				std::cout << "created work directory ~/.inventory-files\n";
			} else {
				std::cout << "could not create ~/.inventory-files\n";
			}
		} else {
			dir.cd(".inventory-files");
		}
	}
	std::cout << "Work directory: " << dir.canonicalPath().toStdString() <<" \n";
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
	sdb.setDatabaseName(dir.canonicalPath() + "/db.sqlite");
	if (!sdb.open()) {
		std::cout << "Could not open database\n";
	}
    
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
	{
		m_pDirectoryWidget = new QWidget();
		m_pTableView_Directories = new QTableView();
		m_pDirectoryModel = new DirectoryModel();
		m_pTableView_Directories->setModel( m_pDirectoryModel );
 		
		m_pDirectoryLayout = new QVBoxLayout();
		m_pDirectoryLayout->addWidget(m_pTableView_Directories);
		m_pDirectoryWidget->setLayout(m_pDirectoryLayout);
	}
	m_pTabWidget->addTab(m_pDirectoryWidget, "Directory for scanning...");
	
	// files tab // todo
	{
		
	}
	m_pTabWidget->addTab(new QWidget(), "Files");

	// Main Layout
	m_pMainLayout = new QVBoxLayout();
    m_pMainLayout->addWidget(m_pTabWidget);
    
    setCentralWidget(m_pTabWidget);
}

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
