#include "job.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QSqlQuery>

Job::Job(QSqlDatabase *pDB, QString sStartDir) {
	m_pDB = pDB;
	m_sStartDir = sStartDir;
	m_nCountFiles = 0;
}

// ---------------------------------------------------------------------

void Job::run() {
	m_stackDirs.clear();
	m_stackDirs.push(m_sStartDir);
	
	while(m_stackDirs.size() > 0) {
		QDir dir(m_stackDirs.pop());
		QFileInfoList files = dir.entryInfoList();
		foreach (QFileInfo file, files) {
			if (file.isDir()){
				if (file.fileName() != "." && file.fileName() != "..") {
					m_stackDirs.push(file.canonicalFilePath());
				}
			}else{
				// todo add to database
				QString sFilePath = file.canonicalFilePath();

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
					query.bindValue(":ext", file.suffix());
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
}

// ---------------------------------------------------------------------

int Job::countFiles() const {
	return m_nCountFiles;
}
