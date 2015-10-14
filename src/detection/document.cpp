#include "document.h"

void DetectionDocument::types(QStringList &list) {
	list << "Document";
}

// --------------------------------------------------------------------

bool DetectionDocument::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "DOC" || sSuffix == "ODT" || sSuffix == "PDF");
	if (bType) {
		type = "Document";
		subtype = "todo"; // version and another information
	}
	return bType;
}
