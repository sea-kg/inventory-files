#include "python.h"

void DetectionPython::types(QStringList &list) {
	list << "Python";
}

// --------------------------------------------------------------------

bool DetectionPython::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "PY");
	if (bType) {
		type = "Python";
		subtype = "todo"; // version and another information
	}
	return bType;
}
