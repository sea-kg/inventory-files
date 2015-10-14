#include "dia.h"

void DetectionDia::types(QStringList &list) {
	list << "Dia";
}

// --------------------------------------------------------------------

bool DetectionDia::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "DIA");
	if (bType) {
		type = "Dia";
		subtype = "todo"; // version and another information
	}
	return bType;
}
