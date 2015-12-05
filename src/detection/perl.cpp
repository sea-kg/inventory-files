#include "perl.h"

void DetectionPerl::types(QStringList &list) {
	list << "Perl";
}

// --------------------------------------------------------------------

bool DetectionPerl::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "PL");
	if (bType) {
		type = "Perl";
		subtype = "todo"; // version and another information
	}
	return bType;
}
