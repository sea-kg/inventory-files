#include "json.h"

void DetectionJson::types(QStringList &list) {
	list << "JSON";
}

// --------------------------------------------------------------------

bool DetectionJson::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "JSON");
	if (bType) {
		type = "JSON";
		subtype = "todo"; // version and another information
	}
	return bType;
}
