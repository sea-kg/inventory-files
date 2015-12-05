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
	// read first line: #! /bin/sh
	bool bType = (sSuffix == "SH"
		|| sName == "COMPILE"
		|| sName == "CONFIGURE"
		|| sName == "KTSHELL"
	);
	if (bType) {
		type = "Shell Script";
		subtype = "todo"; // version and another information
	}
	return bType;
}
