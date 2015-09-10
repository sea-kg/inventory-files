#include "filesmodel.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QSqlQuery>
#include <iostream>

FilesModel::FilesModel(QSqlDatabase *pDB) : QAbstractTableModel(0) {
	m_pDB = pDB;
}

// ---------------------------------------------------------------------

int FilesModel::rowCount(const QModelIndex & /*parent*/) const {
    int nResult = foundRecords();
    std::cout << nResult;
	return nResult > 50 ? 50 : nResult;
}

// ---------------------------------------------------------------------

int FilesModel::columnCount(const QModelIndex & /*parent*/) const {
    return 8;
}

// ---------------------------------------------------------------------

QVariant FilesModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
		QStringList listName;
		QStringList listExt;
		QStringList listType;
		QStringList listSize;
		QStringList listComment;
		QStringList listPath;
		QStringList listMD5;
		QStringList listLastscanning;

		QSqlQuery query(*m_pDB);
		
		if (m_sSearchText == "") {
			query.prepare("SELECT * FROM files LIMIT 50");
		} else {
			query.prepare("SELECT * FROM files WHERE path LIKE :path OR ext = :ext OR comment = :comment LIMIT 50");
			query.bindValue(":path", "%" + m_sSearchText + "%");
			query.bindValue(":ext", m_sSearchText);
			query.bindValue(":comment", m_sSearchText);
		}
		query.exec();

		int fieldName = query.record().indexOf("name");
		int fieldExt = query.record().indexOf("ext");
		int fieldType = query.record().indexOf("type");
		int fieldSize = query.record().indexOf("size");
		int fieldComment = query.record().indexOf("comment");
		int fieldPath = query.record().indexOf("path");
		int fieldMD5 = query.record().indexOf("md5");
		int fieldLastScanning = query.record().indexOf("lastscanning");
		
		while (query.next()) {
			listName << query.value(fieldName).toString();
			listExt << query.value(fieldExt).toString();
			listType << query.value(fieldType).toString();
			listSize << query.value(fieldSize).toString();
			listComment << query.value(fieldComment).toString();
			listPath << query.value(fieldPath).toString();
			listMD5 << query.value(fieldMD5).toString();
			listLastscanning << query.value(fieldLastScanning).toString();
		}

		if (index.row() < listName.size() && index.column() == 0) {
			return listName[index.row()];
		}
		if (index.row() < listExt.size() && index.column() == 1) {
			return listExt[index.row()];
		}
    }
    return QVariant();
}

// ---------------------------------------------------------------------

QVariant FilesModel::headerData(int section, Qt::Orientation  orientation, int role) const {
	if (role != Qt::DisplayRole) {
        return QVariant();
	}
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		if (section == 0)
			return "Name";
		else if (section == 1)
			return "Ext";
		else if (section == 2)
			return "Type";
		else if (section == 3)
			return "Size";
		else if (section == 4)
			return "Comment";
		else if (section == 5)
			return "Path";
		else if (section == 6)
			return "md5";
		else if (section == 7)
			return "Datetime";
		else
			return QVariant();
    }
    if (orientation == Qt::Vertical && role == Qt::DisplayRole) {
        return section + 1;
    }
    return QVariant();
}

// ---------------------------------------------------------------------

void FilesModel::needReset() {
	// QModelIndex topLeft = index(0, 0);
    // QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);
    // emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

// ---------------------------------------------------------------------

void FilesModel::setSearchText(QString sSearchText) {
	m_sSearchText = sSearchText;
}

// ---------------------------------------------------------------------

int FilesModel::foundRecords() const {
	int nResult = 0;
	{
		QSqlQuery query(*m_pDB);
		if (m_sSearchText != "" ) {
			query.prepare("SELECT count(*) as cnt FROM files WHERE path LIKE :path OR ext = :ext OR comment = :comment");
			query.bindValue(":path", "%" + m_sSearchText + "%");
			query.bindValue(":ext", m_sSearchText);
			query.bindValue(":comment", m_sSearchText);
		} else {
			query.prepare("SELECT count(*) as cnt FROM files");
		}
		query.exec();
		if (query.next()) {
			nResult = query.value(0).toInt();
		}
	}
	return nResult;
}
