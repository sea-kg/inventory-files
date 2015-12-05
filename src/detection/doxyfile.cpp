#include "doxyfile.h"

void DetectionDoxyfile::types(QStringList &list) {
	list << "Doxyfile";
}

// --------------------------------------------------------------------

bool DetectionDoxyfile::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "DOXYFILE"
		|| sName == "DOXYFILE"
		|| sName == "DOXYFILE.AM"
		|| sName == "DOXYFILE.GLOBAL"
	);
	if (bType) {
		type = "Doxyfile";
		subtype = "todo"; // version and another information
	}
	return bType;
}
