#include "soundforgepeakfile.h"

void DetectionSoundForgePeakFile::types(QStringList &list) {
	list << "Sound Forge Audio Peak File";
}

// --------------------------------------------------------------------

bool DetectionSoundForgePeakFile::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	// http://open-file.ru/types/sfk
	// HEAD:
	// HEX: 53 46 50 4B 01 00 00 00 40 00 00 00
	// ASCII: SFPK....@
	bool bType = (sSuffix == "SFK");
	if (bType) {
		type = "Sound Forge Audio Peak File";
		subtype = "todo"; // version and another information
	}
	return bType;
}
