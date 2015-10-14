#include "xml.h"

void DetectionXML::types(QStringList &list) {
	list << "XML";
}

// --------------------------------------------------------------------

bool DetectionXML::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "XML");
	if (bType) {
		type = "XML";
		subtype = "todo"; // version and another information
	}
	return bType;
}
