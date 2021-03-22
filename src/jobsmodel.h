#ifndef JOBS_MODEL_H
#define JOBS_MODEL_H

#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QtSql>
#include <QStringList>
#include "job.h"
#include "inotify_service.h"

class JobsModel : public QAbstractTableModel
{
		Q_OBJECT
	private:
		QSqlDatabase *m_pDB;
		QString m_sSearchText;
		QMap<QString, Job*> m_mapJobs;
		
	public:
		JobsModel(QSqlDatabase *pDB);
		int rowCount(const QModelIndex &parent = QModelIndex()) const ;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		QVariant headerData(int section, Qt::Orientation  orientation, int role) const;
		void needReset();
		void terminateJob(QString sPath);
		void terminateAllJobs();
		void runJob(QString sPath, INotifyService *pNotifyService);
		// void setSearchText(QString sSearchText);
		// int foundRecords() const;
	signals:

	public slots:

};

#endif // JOBS_MODEL_H
