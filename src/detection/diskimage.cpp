#include "diskimage.h"

void DetectionDiskImage::types(QStringList &list) {
	list << "Disk Image";
}

// --------------------------------------------------------------------

bool DetectionDiskImage::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	// https://en.wikipedia.org/wiki/Disk_image
	bool bType = (sSuffix == "ISO"
		|| sSuffix == "MDF"
		|| sSuffix == "MDS"
		|| sSuffix == "MDX"
		|| sSuffix == "CUE"
		|| sSuffix == "NRG"
		|| sSuffix == "DAA"
		|| sSuffix == "PQI"
		|| sSuffix == "DMG"
		|| sSuffix == "CCD"
		|| sSuffix == "IMG"
		|| sSuffix == "SUB"
		|| sSuffix == "DVD"
		|| sSuffix == "ISZ"
		|| sSuffix == "CDI"
		|| sSuffix == "PDI"
		|| sSuffix == "UIF"
		|| sSuffix == "CSO"
		|| sSuffix == "BWT"
		|| sSuffix == "B5T"
		|| sSuffix == "B5I"
		|| sSuffix == "B6T"
		|| sSuffix == "B6I"
		|| sSuffix == "BWS"
		|| sSuffix == "BWI" 
	);
	if (bType) {
		type = "Disk Image";
		subtype = "todo"; // version and another information
	}
	return bType;
}
