#include "setup.h"

void DetectionSetup::types(QStringList &list) {
	list << "Setup";
}

// --------------------------------------------------------------------

bool DetectionSetup::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "MSI" || sSuffix == "DEB");
	if (bType) {
		type = "Setup";
		subtype = "todo"; // version and another information
	}
	return bType;
}
