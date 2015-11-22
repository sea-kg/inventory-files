#include "binarydata.h"

void DetectionBinaryData::types(QStringList &list) {
	list << "Binary Data";
}

// --------------------------------------------------------------------

bool DetectionBinaryData::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "DAT");
	if (bType) {
		type = "Binary Data";
		subtype = "todo"; // version and another information
	}
	return bType;
}
