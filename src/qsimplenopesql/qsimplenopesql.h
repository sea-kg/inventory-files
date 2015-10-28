#ifndef QSIMPLENOPESQL_H
#define QSIMPLENOPESQL_H

#include <QString>
#include <QList>
#include "qsimplenopesql_doc.h"

class QSimpleNopeSQL
{
	private:
		QString m_sDir;
	public:
		QSimpleNopeSQL(const QString &sDir);
		
		void add(QSimpleNopeSQL_Doc *pDoc); // insert or update
		void remove(const QString &sDocId);
		bool constains(const QString &sDocId);
		QSimpleNopeSQL_Doc *get(const QString &sDocId);
		// void search(QList<QSimpleNopeSQL_Doc *>);
		// filter
};

#endif // QSIMPLENOPESQL_H
