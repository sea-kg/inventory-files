#include "makefile.h"

void DetectionMakefile::types(QStringList &list) {
	list << "Makefile";
}

// --------------------------------------------------------------------

bool DetectionMakefile::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sName == "MAKEFILE");
	if (bType) {
		type = "Makefile";
		subtype = "todo"; // version and another information
	}
	return bType;
}
