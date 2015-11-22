#include "playlist.h"

void DetectionPlayList::types(QStringList &list) {
	list << "Play List";
}

// --------------------------------------------------------------------

bool DetectionPlayList::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "M3U");
	if (bType) {
		type = "Play List";
		subtype = "todo"; // version and another information
	}
	return bType;
}
