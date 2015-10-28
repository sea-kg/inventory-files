#ifndef QSIMPLENOPESQL_DOC_H
#define QSIMPLENOPESQL_DOC_H

#include <QString>
#include <QMap>
#include <QList>

class QSimpleNopeSQL_Doc
{
	private:
		QString m_sDocId;
		QMap<QString,QString> m_mapFields;
	public:
		QSimpleNopeSQL_Doc(const QString &sDocId);
		void add(QString fieldName, QList<QString> fieldValue);
		void add(QString fieldName, QString fieldValue);
		void remove(QString fieldName);
		bool contains(QString fieldName);
		QList<QString> get(QString fieldName);
		QString toJson();
		QMap<QString,QString> &fields();

};

#endif // QSIMPLENOPESQL_DOC_H
