#include "mercurial.h"

void DetectionMercurial::types(QStringList &list) {
	list << "Mercurial";
}

// --------------------------------------------------------------------

bool DetectionMercurial::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "HG"
		|| (sName == "REQUIRES" && sPath.contains(".HG/REQUIRES"))
		|| (sSuffix == "BOOKMARKS" && sPath.contains(".HG/UNDO."))
		|| (sSuffix == "BRANCH" && sPath.contains(".HG/UNDO."))
		|| (sSuffix == "DESC" && sPath.contains(".HG/UNDO."))
		|| (sSuffix == "DIRSTATE" && sPath.contains(".HG/UNDO."))
		|| (sSuffix == "" && sPath.contains(".HG/BRANCH"))
		|| (sSuffix == "" && sPath.contains(".HG/DIRSTATE"))
		|| (sSuffix == "" && sPath.contains(".HG/HGRC"))
		|| (sSuffix == "" && sPath.contains(".HG/CACHE/"))
		|| (sSuffix == "HGTAGS")
		|| (sSuffix == "I" && sPath.contains(".HG/00CHANGELOG.I"))
		|| (sPath.contains(".HG/STORE/"))
	);
	
	if (bType) {
		type = "Mercurial";
		subtype = "todo"; // version and another information
	}
	return bType;
}
