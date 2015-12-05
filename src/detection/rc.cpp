#include "rc.h"

void DetectionRC::types(QStringList &list) {
	list << "Compiler Resource File";
}

// --------------------------------------------------------------------

bool DetectionRC::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "RC");
	if (bType) {
		type = "Compiler Resource File";
		subtype = "todo"; // version and another information
	}
	return bType;
}
