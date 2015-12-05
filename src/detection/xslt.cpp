#include "xslt.h"

void DetectionXSLT::types(QStringList &list) {
	list << "XSLT";
}

// --------------------------------------------------------------------

bool DetectionXSLT::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "XSL");
	if (bType) {
		type = "XSLT";
		subtype = "todo"; // version and another information
	}
	return bType;
}
