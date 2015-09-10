#ifndef JOB_H
#define JOB_H

#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QtSql>
#include <QStringList>
#include <QThread>

class Job : public QThread
{
		Q_OBJECT
	private:
		QSqlDatabase *m_pDB;
		QString m_sStartDir;
		QStack<QString> m_stackDirs;
		int m_nCountFiles;
		QString m_sState;
	public:
		Job(QSqlDatabase *pDB, QString sStartDir);
		
		int countFiles() const;
		QString state() const;
		
	protected:
		void run();
    
	signals:

	public slots:

};

#endif // JOB_H
