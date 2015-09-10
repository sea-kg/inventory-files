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

#include "directorymodel.h"

class MainWindow : public QMainWindow
{
	// private:
		Q_OBJECT
	private:
		QTabWidget *m_pTabWidget;
		QVBoxLayout *m_pMainLayout;
		QVBoxLayout *m_pDirectoryLayout;
		QTableView *m_pTableView_Directories;
		QWidget *m_pDirectoryWidget;
		DirectoryModel *m_pDirectoryModel;
		QMenu *m_pMenuHelp;
		QAction *m_pActionLicense;
	public:

		MainWindow();
		
	signals:

	public slots:
		
		
	private slots:
		void actionLicense();
};

#endif // MAIN_WIDGET_H
