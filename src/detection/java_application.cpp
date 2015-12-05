#include "java_application.h"

void DetectionJavaApplication::types(QStringList &list) {
	list << "Java Application";
}

// --------------------------------------------------------------------

bool DetectionJavaApplication::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "JAR");
	if (bType) {
		type = "Java Application";
		subtype = "todo"; // version and another information
	}
	return bType;
}
