#include "translations.h"

void DetectionTranslations::types(QStringList &list) {
	list << "Translations";
}

// --------------------------------------------------------------------

bool DetectionTranslations::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "PO");
	if (bType) {
		type = "Translations";
		subtype = "todo"; // version and another information
	}
	return bType;
}
