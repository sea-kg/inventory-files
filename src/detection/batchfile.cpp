#include "batchfile.h"

void DetectionBatchFile::types(QStringList &list) {
	list << "Batch File";
}

// --------------------------------------------------------------------

bool DetectionBatchFile::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "BAT");
	if (bType) {
		type = "Batch File";
		subtype = "todo"; // version and another information
	}
	return bType;
}
