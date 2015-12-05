#include "logfile.h"

void DetectionLogFile::types(QStringList &list) {
	list << "Log File";
}

// --------------------------------------------------------------------

bool DetectionLogFile::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "LOG" || sSuffix == "AUTOCONF_TRACE");
	if (bType) {
		type = "Log File";
		subtype = "todo"; // version and another information
	}
	return bType;
}
