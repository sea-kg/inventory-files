#include "sourcecodecpp.h"

void DetectionSourceCodeCpp::types(QStringList &list) {
	list << "C++/C";
}

// --------------------------------------------------------------------

bool DetectionSourceCodeCpp::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "CPP" || sSuffix == "C" || sSuffix == "H");
	if (bType) {
		type = "C++/C";
		subtype = "todo"; // version and another information
	}
	return bType;
}
