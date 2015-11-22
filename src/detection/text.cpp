#include "text.h"

void DetectionText::types(QStringList &list) {
	list << "Text";
}

// --------------------------------------------------------------------

bool DetectionText::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "TXT" || sSuffix == "SRT");
	if (bType) {
		type = "Text";
		subtype = "todo"; // version and another information
	}
	return bType;
}
