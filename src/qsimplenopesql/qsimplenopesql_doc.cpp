#include "qsimplenopesql_doc.h"
#include <iostream>

QSimpleNopeSQL_Doc::QSimpleNopeSQL_Doc(const QString &sDocId) {
	m_sDocId = sDocId;
}

// ---------------------------------------------------------------------

void QSimpleNopeSQL_Doc::add(QString fieldName, QList<QString> fieldValue) {
	// TODO
}

// ---------------------------------------------------------------------

void QSimpleNopeSQL_Doc::add(QString fieldName, QString fieldValue) {
	// TODO
}

// ---------------------------------------------------------------------

void QSimpleNopeSQL_Doc::remove(QString fieldName) {
	// TODO
}

// ---------------------------------------------------------------------

bool QSimpleNopeSQL_Doc::contains(QString fieldName) {
	// TODO
}

// ---------------------------------------------------------------------

QList<QString> QSimpleNopeSQL_Doc::get(QString fieldName) {
	// TODO
	return QList<QString>();
}

// ---------------------------------------------------------------------

QString QSimpleNopeSQL_Doc::toJson() {
	return "TODO";
}

// ---------------------------------------------------------------------

QMap<QString,QString> &QSimpleNopeSQL_Doc::fields() {
	return m_mapFields;
}

// ---------------------------------------------------------------------
