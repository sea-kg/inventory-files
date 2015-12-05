#include "shellscript.h"

void DetectionShellScript::types(QStringList &list) {
	list << "Shell Script";
}

// --------------------------------------------------------------------

bool DetectionShellScript::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "SH"
		|| sName == "COMPILE"
		|| sName == "CONFIGURE"
	);
	if (bType) {
		type = "Shell Script";
		subtype = "todo"; // version and another information
	}
	return bType;
}
