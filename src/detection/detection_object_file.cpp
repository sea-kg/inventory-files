#include "detection_object_file.h"

void DetectionObjectFile::types(QStringList &list) {
	list << "Object";
}

// --------------------------------------------------------------------

bool DetectionObjectFile::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "O");
	if (bType) {
		type = "Object";
		subtype = "todo"; // version and another information
	}
	return bType;
}
