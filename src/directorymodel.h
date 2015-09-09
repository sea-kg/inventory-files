#ifndef DIRECTORY_MODEL_H
#define DIRECTORY_MODEL_H

#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>

class DirectoryModel : public QAbstractTableModel
{
		Q_OBJECT
	private:

	public:
		DirectoryModel(QWidget *parent = 0);
		int rowCount(const QModelIndex &parent = QModelIndex()) const ;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	signals:

	public slots:
};

#endif // DIRECTORY_MODEL_H
