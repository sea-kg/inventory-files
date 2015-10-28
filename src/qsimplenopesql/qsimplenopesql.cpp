#include "qsimplenopesql.h"
#include <iostream>

QSimpleNopeSQL::QSimpleNopeSQL(const QString &sDir) {
	m_sDir = sDir;
}

// ---------------------------------------------------------------------

void QSimpleNopeSQL::add(QSimpleNopeSQL_Doc *pDoc) {
	// TODO
	pDoc->fields();
}

// ---------------------------------------------------------------------
