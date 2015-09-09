#include "directorymodel.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QApplication>

DirectoryModel::DirectoryModel(QWidget *parent)
    : QAbstractTableModel(parent)
{
}

int DirectoryModel::rowCount(const QModelIndex & /*parent*/) const {
   return 2;
}

int DirectoryModel::columnCount(const QModelIndex & /*parent*/) const {
    return 3;
}

QVariant DirectoryModel::data(const QModelIndex &index, int role) const {

    if (role == Qt::DisplayRole) {
       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    }
    return QVariant();
}
