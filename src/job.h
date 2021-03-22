#ifndef JOB_H
#define JOB_H

#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QtSql>
#include <QStringList>
#include <QThread>
#include "detection/detection.h"
#include "inotify_service.h"

class Job : public QThread
{
		Q_OBJECT
	private:
		QSqlDatabase *m_pDB;
		Detection *m_pDetection;
		QString m_sStartDir;
		QStack<QString> m_stackDirs;
		int m_nCountFiles;
		QString m_sState;
		INotifyService *m_pNotifyService;

	public:
		Job(QSqlDatabase *pDB, QString sStartDir, INotifyService *pNotifyService);
		
		int countFiles() const;
		QString getState() const;
		
	protected:
		void run();
    
	signals:

	public slots:

};

#endif // JOB_H
