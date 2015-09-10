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
}

// ---------------------------------------------------------------------

void Job::run() {
	m_stackDirs.clear();
	m_stackDirs.push(m_sStartDir);
	
	m_sState = "Checking...";
	// todo check existing files

	m_sState = "Scanning...";
	while(m_stackDirs.size() > 0) {
		QDir dir(m_stackDirs.pop());
		// std::cout << "Scan in " << dir.canonicalPath().toStdString() << "\n";
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
				
				if (!bContains) {
					QSqlQuery query(*m_pDB);
					query.prepare("INSERT INTO files(path,name,md5,comment,ext,type,size,lastscanning) "
						"VALUES(:path,:name,:md5,:comment,:ext,:type,:size,CURRENT_TIMESTAMP)");
					query.bindValue(":path", sFilePath);
					query.bindValue(":name", file.fileName());
					query.bindValue(":md5", "TODO");
					query.bindValue(":comment", "");
					query.bindValue(":ext", file.suffix().toUpper());
					query.bindValue(":type", "Unknown");
					query.bindValue(":size", file.size());
					query.exec();
				} else {
					// todo optimize update 
					QSqlQuery query(*m_pDB);
					query.prepare("UPDATE files SET "
						" md5 = :md5, "
						" type = :type, "
						" size = :size, "
						" lastscanning = CURRENT_TIMESTAMP"
						" WHERE path = :path"
						"VALUES(:path,:name,:md5,:comment,:ext,:type,:size,CURRENT_TIMESTAMP)");
					query.bindValue(":md5", "TODO");
					query.bindValue(":type", "Unknown");
					query.bindValue(":size", file.size());
					query.exec();
				}
				// std::cout << "FILE: " << sFilePath.toStdString() << "\n";
			}
		}
	}
	m_sState = "Completed";
}

// ---------------------------------------------------------------------

int Job::countFiles() const {
	return m_nCountFiles;
}
