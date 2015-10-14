#include "config.h"

void DetectionConfig::types(QStringList &list) {
	list << "Config";
}

// --------------------------------------------------------------------

bool DetectionConfig::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "INI" || sSuffix == "CONF");
	if (bType) {
		type = "Config";
		subtype = "todo"; // version and another information
	}
	return bType;
}

