#include "jobsmodel.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QSqlQuery>
#include <iostream>

JobsModel::JobsModel(QSqlDatabase *pDB) : QAbstractTableModel(0) {
	m_pDB = pDB;
}

// ---------------------------------------------------------------------

int JobsModel::rowCount(const QModelIndex & /*parent*/) const {
	return m_mapJobs.size();
}

// ---------------------------------------------------------------------

int JobsModel::columnCount(const QModelIndex & /*parent*/) const {
    return 3;
}

// ---------------------------------------------------------------------

QVariant JobsModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
		QList<QString> jobs = m_mapJobs.keys();
		if (index.row() < jobs.size()) {
			QString sPath = jobs[index.row()];
			Job *pJob = m_mapJobs[sPath];
			if (index.column() == 0) {
				return sPath;
			} else if (index.column() == 1) {
				return pJob->state();
			} else if (index.column() == 2) {
				return pJob->countFiles();
			}
		}
    }
    return QVariant();
}

// ---------------------------------------------------------------------

QVariant JobsModel::headerData(int section, Qt::Orientation  orientation, int role) const {
	if (role != Qt::DisplayRole) {
        return QVariant();
	}
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		if (section == 0)
			return "Path";
		else if (section == 1)
			return "State";
		else if (section == 2)
			return "FilesCount";
		else
			return QVariant();
    }
    if (orientation == Qt::Vertical && role == Qt::DisplayRole) {
        return section + 1;
    }
    return QVariant();
}

// ---------------------------------------------------------------------

void JobsModel::needReset() {
	// QModelIndex topLeft = index(0, 0);
    // QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);
    // emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

// ---------------------------------------------------------------------

void JobsModel::terminateJob(QString sPath) {
	if (m_mapJobs.contains(sPath)) {
		if (m_mapJobs[sPath]->isFinished()) {
			std::cout << " job finished\n";
			m_mapJobs.remove(sPath);
			std::cout << "removed job.\n";
		} else {
			std::cout << "stopping job...\n";
			Job *pJob = m_mapJobs[sPath];
			pJob->terminate();
			while (!pJob->isFinished()) {
				std::cout << "stopping job...\n";
			}
			m_mapJobs.remove(sPath);
			std::cout << "removed job.\n";
		}
		this->needReset();
	}
}

// ---------------------------------------------------------------------

void JobsModel::runJob(QString sPath) {
	Job *pJob = new Job(m_pDB, sPath);
	if (!m_mapJobs.contains(sPath)) {
		m_mapJobs[sPath] = pJob;
		pJob->start();
	} else {
		std::cout << " job already exists\n";
	}
	this->needReset();
}

// ---------------------------------------------------------------------

void JobsModel::terminateAllJobs() {
	// todo
	this->needReset();
}
