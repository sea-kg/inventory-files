#include "sign.h"

void DetectionSign::types(QStringList &list) {
	list << "Signature";
}

// --------------------------------------------------------------------

bool DetectionSign::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "ASC" || sSuffix == "SIG");
	if (bType) {
		type = "Signature";
		subtype = "todo"; // version and another information
	}
	return bType;
}
