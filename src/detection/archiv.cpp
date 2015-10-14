#include "archiv.h"

void DetectionArchiv::types(QStringList &list) {
	list << "Archiv";
}

// --------------------------------------------------------------------

bool DetectionArchiv::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "RAR" || sSuffix == "ZIP");
	if (bType) {
		type = "Archiv";
		subtype = "todo"; // version and another information
	}
	return bType;
}