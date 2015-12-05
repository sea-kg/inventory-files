#include "backup.h"

void DetectionBackup::types(QStringList &list) {
	list << "Backup";
}

// --------------------------------------------------------------------

bool DetectionBackup::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "BAK" || sSuffix == "ORIG"
		|| (sSuffix == "IN" && sName != "MAKEFILE.IN")
	);
	if (bType) {
		type = "Backup";
		subtype = "todo"; // version and another information
	}
	return bType;
}
