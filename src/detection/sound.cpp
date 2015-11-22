#include "sound.h"

void DetectionSound::types(QStringList &list) {
	list << "Sound";
}

// --------------------------------------------------------------------

bool DetectionSound::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "WAV" || sSuffix == "FLAC" || sSuffix == "MP3");
	if (bType) {
		type = "Sound";
		subtype = "todo"; // version and another information
	}
	return bType;
}
