#include "css.h"

void DetectionCSS::types(QStringList &list) {
	list << "CSS";
}

// --------------------------------------------------------------------

bool DetectionCSS::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "CSS");
	if (bType) {
		type = "CSS";
		subtype = "todo"; // version and another information
	}
	return bType;
}

