#include "binary_diff.h"

void DetectionBinaryDiff::types(QStringList &list) {
	list << "Binary Differential File";
}

// --------------------------------------------------------------------

bool DetectionBinaryDiff::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "XDELTA");
	if (bType) {
		type = "Binary Differential File";
		subtype = "todo"; // version and another information
	}
	return bType;
}
