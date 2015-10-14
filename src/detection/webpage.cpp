#include "webpage.h"

void DetectionWebPage::types(QStringList &list) {
	list << "Web Page";
}

// --------------------------------------------------------------------

bool DetectionWebPage::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "HTML");
	if (bType) {
		type = "Web Page";
		subtype = "todo"; // version and another information
	}
	return bType;
}
