#include "project.h"

void DetectionProject::types(QStringList &list) {
	list << "Project";
}

// --------------------------------------------------------------------

bool DetectionProject::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "PRO" || sSuffix == "KDEVELOP");
	if (bType) {
		type = "Project";
		subtype = "todo"; // version and another information
	}
	return bType;
}
