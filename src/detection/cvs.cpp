#include "cvs.h"

void DetectionCVS::types(QStringList &list) {
	list << "CVS";
}

// --------------------------------------------------------------------

bool DetectionCVS::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)

	bool bType = (sName == "ROOT" && sPath.contains("CVS/ROOT"))
		|| (sName == "REPOSITORY" && sPath.contains("CVS/REPOSITORY"))
		|| (sName == "ENTRIES" && sPath.contains("CVS/ENTRIES"))
		|| (sName == "ENTRIES.EXTRA" && sPath.contains("CVS/ENTRIES.EXTRA"))
		|| (sName == "ENTRIES.EXTRA.OLD" && sPath.contains("CVS/ENTRIES.EXTRA.OLD"))
		|| (sName == "ENTRIES.OLD" && sPath.contains("CVS/ENTRIES.OLD"))
		|| (sName == ".CVSIGNORE")
	;
	if (bType) {
		type = "CVS";
		subtype = "todo"; // version and another information
	}
	return bType;
}
