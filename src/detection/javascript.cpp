#include "javascript.h"

void DetectionJavaScript::types(QStringList &list) {
	list << "JavaScript";
	list << "JQuery";
}

// --------------------------------------------------------------------

bool DetectionJavaScript::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "JS");
	if (bType) {
		type = "JavaScript";
		if (sName.contains("JQUERY"))
			type = "JQuery";
		subtype = "todo"; // version and another information
	}
	return bType;
}
