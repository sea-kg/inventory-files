#include "mainwidget.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QFileInfo>
#include <qmath.h>
#include <iostream>
#include <QApplication>
#include <QDir>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
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
    
	m_pTabWidget = new QTabWidget(this);

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
    
	this->setLayout(m_pMainLayout);
}
