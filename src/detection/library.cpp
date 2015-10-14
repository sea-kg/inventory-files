#include "library.h"

void DetectionLibrary::types(QStringList &list) {
	list << "Library";
}

// --------------------------------------------------------------------

bool DetectionLibrary::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "SO" || sSuffix == "DLL");
	if (bType) {
		type = "Library";
		subtype = "todo"; // version and another information
	}
	return bType;
}
