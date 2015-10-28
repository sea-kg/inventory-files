#include "font.h"

void DetectionFont::types(QStringList &list) {
	list << "Font";
}

// --------------------------------------------------------------------

bool DetectionFont::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "TTF" || sSuffix == "WOFF" || sSuffix == "EOT");
	if (bType) {
		type = "Font";
		subtype = "todo"; // version and another information
	}
	return bType;
}
