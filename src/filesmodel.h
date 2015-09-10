#ifndef FILES_MODEL_H
#define FILES_MODEL_H

#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QtSql>
#include <QStringList>

class FilesModel : public QAbstractTableModel
{
		Q_OBJECT
	private:
		QSqlDatabase *m_pDB;
		QString m_sSearchText;
	public:
		FilesModel(QSqlDatabase *pDB);
		int rowCount(const QModelIndex &parent = QModelIndex()) const ;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		QVariant headerData(int section, Qt::Orientation  orientation, int role) const;
		void needReset();
		void setSearchText(QString sSearchText);
		int foundRecords() const;
	signals:

	public slots:

};

#endif // FILES_MODEL_H
