#include "manual.h"

void DetectionManual::types(QStringList &list) {
	list << "Manual";
}

// --------------------------------------------------------------------

bool DetectionManual::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "1" && sPath.contains("/DOCS/MAN/"));
	if (bType) {
		type = "Manual";
		subtype = "todo"; // version and another information
	}
	return bType;
}
