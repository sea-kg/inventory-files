#include "application.h"

void DetectionApplication::types(QStringList &list) {
	list << "Application";
}

// --------------------------------------------------------------------

bool DetectionApplication::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "EXE" || sSuffix == "BIN");
	if (bType) {
		type = "Application";
		subtype = "todo"; // version and another information
	}
	return bType;
}
