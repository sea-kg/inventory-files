#include "ruby.h"

void DetectionRuby::types(QStringList &list) {
	list << "Ruby";
}

// --------------------------------------------------------------------

bool DetectionRuby::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "RB");
	if (bType) {
		type = "Ruby";
		subtype = "todo"; // version and another information
	}
	return bType;
}
