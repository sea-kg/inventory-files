#include "torrent.h"

void DetectionTorrent::types(QStringList &list) {
	list << "Torrent";
}

// --------------------------------------------------------------------

bool DetectionTorrent::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "TORRENT" || sSuffix == "THOST");
	if (bType) {
		type = "Torrent";
		subtype = "todo"; // version and another information
	}
	return bType;
}
