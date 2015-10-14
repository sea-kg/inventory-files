#include "php.h"

void DetectionPHP::types(QStringList &list) {
	list << "PHP";
}

// --------------------------------------------------------------------

bool DetectionPHP::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "PHP");
	if (bType) {
		type = "PHP";
		subtype = "todo"; // version and another information
	}
	return bType;
}
