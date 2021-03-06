#ifndef DIRECTORY_MODEL_H
#define DIRECTORY_MODEL_H

#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QtSql>
#include <QStringList>

class DirectoryModel : public QAbstractTableModel
{
		Q_OBJECT
	private:
		QSqlDatabase *m_pDB;
		

	public:
		DirectoryModel(QSqlDatabase *pDB);
		int rowCount(const QModelIndex &parent = QModelIndex()) const ;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		QVariant headerData(int section, Qt::Orientation  orientation, int role) const;
		void needReset();
	signals:

	public slots:
};

#endif // DIRECTORY_MODEL_H
