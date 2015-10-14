#include "image.h"

void DetectionImage::types(QStringList &list) {
	list << "Image";
}

// --------------------------------------------------------------------

bool DetectionImage::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "PNG" || sSuffix == "JPG" || sSuffix == "JPEG" || sSuffix == "GIF" || sSuffix == "SVG");
	if (bType) {
		type = "Image";
		subtype = "todo"; // version and another information
	}
	return bType;
}
