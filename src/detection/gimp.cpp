#include "gimp.h"

void DetectionGimp::types(QStringList &list) {
	list << "Gimp";
}

// --------------------------------------------------------------------

bool DetectionGimp::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "XCF");
	if (bType) {
		type = "Gimp";
		subtype = "todo"; // version and another information
	}
	return bType;
}
