#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QtSql>
#include "directorymodel.h"

class MainWidget : public QWidget
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
	public:

		MainWidget(QWidget *parent = 0);
		
	signals:

	public slots:
};

#endif // MAIN_WIDGET_H
