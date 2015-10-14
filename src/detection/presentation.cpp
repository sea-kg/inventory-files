#include "presentation.h"

void DetectionPresentation::types(QStringList &list) {
	list << "Presentation";
}

// --------------------------------------------------------------------

bool DetectionPresentation::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "PPTX");
	if (bType) {
		type = "Presentation";
		subtype = "todo"; // version and another information
	}
	return bType;
}
