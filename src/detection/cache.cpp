#include "cache.h"

void DetectionCache::types(QStringList &list) {
	list << "Cache";
}

// --------------------------------------------------------------------

bool DetectionCache::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = ((sSuffix == "HEU" || sSuffix == "SWZ") && sPath.contains(QString(".adobe/Flash_Player/AssetCache").toUpper()))
		|| (sName == "THUMBS.DB")
		|| (sSuffix == "TMP");
	if (bType) {
		type = "Cache";
		subtype = "todo"; // version and another information
	}
	return bType;
}
