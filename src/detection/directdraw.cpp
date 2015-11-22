#include "directdraw.h"

void DetectionDirectDraw::types(QStringList &list) {
	list << "DirectDraw Surface";
}

// --------------------------------------------------------------------

bool DetectionDirectDraw::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "DDS");
	if (bType) {
		type = "DirectDraw Surface";
		subtype = "todo"; // version and another information
	}
	return bType;
}
