#include "animation.h"

void DetectionAnimation::types(QStringList &list) {
	list << "Animation";
}

// --------------------------------------------------------------------

bool DetectionAnimation::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "SWF");
	if (bType) {
		type = "Animation";
		subtype = "todo"; // version and another information
	}
	return bType;
}
