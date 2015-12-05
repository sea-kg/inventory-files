#include "video.h"

void DetectionVideo::types(QStringList &list) {
	list << "Video";
}

// --------------------------------------------------------------------

bool DetectionVideo::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (
		sSuffix == "MP4"
		|| sSuffix == "AVI"
		|| sSuffix == "MPG"
		|| sSuffix == "MKV"
		|| sSuffix == "FLV"
		|| sSuffix == "MOV"
		|| sSuffix == "WMV"
	);
	if (bType) {
		type = "Video";
		subtype = "todo"; // version and another information
	}
	return bType;
}
