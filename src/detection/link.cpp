#include "link.h"

void DetectionLink::types(QStringList &list) {
	list << "Link";
}

// --------------------------------------------------------------------

bool DetectionLink::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "DESKTOP");
	if (bType) {
		type = "Link";
		subtype = "todo"; // version and another information
	}
	return bType;
}
