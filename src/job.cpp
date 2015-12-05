#include "job.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QSqlQuery>
#include <iostream>

Job::Job(QSqlDatabase *pDB, QString sStartDir) {
	m_pDB = pDB;
	m_sStartDir = sStartDir;
	m_nCountFiles = 0;
	m_sState = "begin";
	m_pDetection = new Detection();
}

// ---------------------------------------------------------------------

void Job::run() {
	m_stackDirs.clear();
	m_stackDirs.push(m_sStartDir);
	
	m_sState = "Checking...";
	m_nCountFiles = 0;
	{
		QSqlQuery query(*m_pDB);
		query.prepare("SELECT path FROM files WHERE path LIKE :path");
		query.bindValue(":path", m_sStartDir + "%");
		query.exec();
		while (query.next()) {
			QString sFilePath = query.value(0).toString();
			m_nCountFiles++;
			if (!QFile::exists(sFilePath)) {
				std::cout << "file not exists: " << sFilePath.toStdString() << "\n";
				QSqlQuery query_remove(*m_pDB);
				query_remove.prepare("DELETE FROM files WHERE path = :path");
				query_remove.bindValue(":path", sFilePath);
				query_remove.exec();
			}
		}
	}

	m_sState = "Scanning...";
	m_nCountFiles = 0;
	while(m_stackDirs.size() > 0) {
		QDir dir(m_stackDirs.pop());
		std::cout << "Scan in " << dir.canonicalPath().toStdString() << "\n";
		QFileInfoList files = dir.entryInfoList(QDir::AllDirs | QDir::Hidden | QDir::Files | QDir::NoSymLinks);
		foreach (QFileInfo file, files) {
			if (file.isDir()) {
				if (file.fileName() != "." && file.fileName() != "..") {
					m_stackDirs.push(file.canonicalFilePath());
					// std::cout << file.canonicalFilePath().toStdString() << "\n";
				}
			}else{
				// todo add to database
				QString sFilePath = file.canonicalFilePath();
				// std::cout << "FILE: " << sFilePath.toStdString() << "\n";

				m_nCountFiles++;
				// try find this file in db
				bool bContains = false;
				{
					QSqlQuery query(*m_pDB);
					query.prepare("SELECT id FROM files WHERE path = :path");
					query.bindValue(":path", sFilePath);
					query.exec();
					if (query.next()) {
						bContains = true; //query.value(0).toString();
					}
				}

				QString sType;
				QString sSubType;
				if (!m_pDetection->isType(file, sType, sSubType)) {
					std::cerr << "Warning: Could not detect type for file: " << sFilePath.toStdString() << "\n";
					sType = "Unknown";
				}
				
				if (!bContains) {
					QSqlQuery query(*m_pDB);
					query.prepare("INSERT INTO files(path,path_upper,name,name_upper,md5,comment,comment_upper,ext,type,size,lastscanning) "
						"VALUES(:path,:path_upper,:name,:name_upper,:md5,:comment,:comment_upper,:ext,:type,:size,CURRENT_TIMESTAMP)");
					query.bindValue(":path", sFilePath);
					query.bindValue(":path_upper", sFilePath.toUpper());
					query.bindValue(":name", file.fileName());
					query.bindValue(":name_upper", file.fileName().toUpper());
					query.bindValue(":md5", "TODO");
					query.bindValue(":comment", "");
					query.bindValue(":comment_upper", "");
					query.bindValue(":ext", file.suffix().toUpper());
					query.bindValue(":type", sType);
					query.bindValue(":size", file.size());
					query.exec();
				} else {
					// todo optimize update
					QSqlQuery query(*m_pDB);
					query.prepare("UPDATE files SET "
						// " md5 = :md5, "
						" type = :type, "
						" size = :size, "
						" lastscanning = CURRENT_TIMESTAMP"
						" WHERE path = :path");
					// query.bindValue(":md5", "TODO");
					query.bindValue(":type", sType);
					query.bindValue(":size", file.size());
					query.bindValue(":path", sFilePath);
					query.exec();
				}
				std::cout << "FILE: " << sFilePath.toStdString() << "\n";
			}
		}
	}
	m_sState = "Completed";
}

// ---------------------------------------------------------------------

int Job::countFiles() const {
	return m_nCountFiles;
}

// ---------------------------------------------------------------------

QString Job::state() const {
	return m_sState;
}

// ---------------------------------------------------------------------
