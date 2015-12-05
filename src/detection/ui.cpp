#include "ui.h"

void DetectionUI::types(QStringList &list) {
	list << "Qt UI";
}

// --------------------------------------------------------------------

bool DetectionUI::isType(const QFileInfo &fi, QString &type, QString &subtype){
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "UI");
	if (bType) {
		type = "Qt UI";
		subtype = "todo"; // version and another information
	}
	return bType;
}
