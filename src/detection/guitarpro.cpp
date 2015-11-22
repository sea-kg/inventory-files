#include "guitarpro.h"

void DetectionGuitarPro::types(QStringList &list) {
	list << "Guitar Pro";
}

// --------------------------------------------------------------------

bool DetectionGuitarPro::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "GP5");
	if (bType) {
		type = "Guitar Pro";
		subtype = "todo"; // version and another information
	}
	return bType;
}
