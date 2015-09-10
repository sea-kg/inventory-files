#include "directorymodel.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QSqlQuery>

DirectoryModel::DirectoryModel(QSqlDatabase *pDB) : QAbstractTableModel(0) {
	m_pDB = pDB;
}

// ---------------------------------------------------------------------

int DirectoryModel::rowCount(const QModelIndex & /*parent*/) const {
	QSqlQuery query(*m_pDB);
    query.prepare("SELECT count(*) as cnt FROM directories");
    query.exec();
    int nResult = 0;
	if (query.next()) {
		nResult = query.value(0).toInt();
	}

	return nResult;
}

// ---------------------------------------------------------------------

int DirectoryModel::columnCount(const QModelIndex & /*parent*/) const {
    return 2;
}

// ---------------------------------------------------------------------

QVariant DirectoryModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
		QStringList listDirs;
		QStringList listLastScanning;
		listDirs.clear();
		listLastScanning.clear();

		QSqlQuery query(*m_pDB);
		query.prepare("SELECT path, lastscanning FROM directories");
		query.exec();
		while (query.next()) {
			listDirs << query.value(0).toString();
			listLastScanning << query.value(1).toString();
		}
		if (index.row() < listDirs.size() && index.column() == 0) {
			return listDirs[index.row()];
		}
		if (index.row() < listLastScanning.size() && index.column() == 1) {
			return listLastScanning[index.row()];
		}
    }
    return QVariant();
}

// ---------------------------------------------------------------------

QVariant DirectoryModel::headerData(int section, Qt::Orientation  orientation, int role) const {
	if (role != Qt::DisplayRole) {
        return QVariant();
	}
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		if (section == 0)
			return "Path";
		else if (section == 1)
			return "Last Scan";
		else
			return QVariant();
    }
    if (orientation == Qt::Vertical && role == Qt::DisplayRole) {
        return section + 1;
    }
    return QVariant();
}

// ---------------------------------------------------------------------

void DirectoryModel::needReset() {
	// QModelIndex topLeft = index(0, 0);
    // QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);

    // emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}
