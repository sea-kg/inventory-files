#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>

#include "directorymodel.h"
#include "filesmodel.h"

class MainWindow : public QMainWindow
{
	// private:
		Q_OBJECT
	private:
		QSqlDatabase *m_pDB;
		
		QTabWidget *m_pTabWidget;
		QVBoxLayout *m_pMainLayout;
		QMenu *m_pMenuHelp;
		QAction *m_pActionLicense;
		
		QWidget *m_pDirectoryWidget;
		QTableView *m_pTableView_Directories;
		DirectoryModel *m_pDirectoryModel;

		QWidget *m_pFilesWidget;
		QTableView *m_pTableView_Files;
		QLineEdit *m_pLineEditSearch;
		FilesModel *m_pFilesModel;
		QLabel *m_pLabelResult;
		
		QWidget *m_pJobsWidget;

		QString m_sWorkDirectory;
		
	private:
		void initConnection();
		void initDirectoryTabs();
		void initFilesTabs();
		void initJobsTabs();

	public:

		MainWindow(QString sWorkDirectory);
		
	signals:

	public slots:
		
	private slots:
		void actionLicense();
		void btnInsertDirectory();
		void btnRemoveDirectory();
		void btnScanDirectory();
		void btnFilesSearch();
};

#endif // MAIN_WIDGET_H
