#include "unknown.h"

virtual QString DetectionUnknown::type() {
	return "Unknown";
};

virtual bool DetectionUnknown::isType() {
	return true;
}

// ---------------------------------------------------------------------

QString detectType(QFileInfo &file) {
	QString sSuffix = file.suffix().toUpper();
	QString sPath = file.canonicalFilePath().toUpper();
	QString sName = file.fileName().toUpper();
	
	if (sSuffix == "INI" || sSuffix == "CONF") {
		return "Config";
	} else if (sSuffix == "TXT") {
		return "Text";
	} else if (sSuffix == "PPTX") {
		return "Presentation";
	} else if (sSuffix == "XML") {
		return "XML";
	} else if (sSuffix == "LOG") {
		return "Log";
	} else if (sSuffix == "SWF") {
		return "Small Web Format";
	} else if (sSuffix == "MP4") {
		return "Video";
	} else if (sSuffix == "EXE") {
		return "Application";
	} else if (sSuffix == "SO" || sSuffix == "DLL") {
		return "Library";
	} else if (sSuffix == "XCF") {
		return "Gimp";
	} else if (sSuffix == "JS" && sName.contains(QString("jquery").toUpper())) {
		return "JQuery";
	} else if (sSuffix == "JS") {
		return "Java Script";
	} else if (sSuffix == "DOC") {
		return "Java Script";
	} else if (sSuffix == "CSS") {
		return "CSS";
	} else if (sSuffix == "DOC" || sSuffix == "PDF" || sSuffix == "ODT") {
		return "Document";
	} else if (sSuffix == "HTML") {
		return "Web Page";
	} else if (sSuffix == "py") {
		return "Python";
	} else if (sSuffix == "cpp" || sSuffix == "c" || sSuffix == "h") {
		return "C++/C";
	} else if (sSuffix == "OVA") {
		return "Virtual Machine";
	} else if (sSuffix == "RAR" || sSuffix == "ZIP") {
		return "Archiv";
	} else if (sSuffix == "WAV" || sSuffix == "FLAC") {
		return "Sound";
	} else if (sSuffix == "PNG" || sSuffix == "JPG" || sSuffix == "JPEG" || sSuffix == "GIF" || sSuffix == "SVG") {
		return "Images";
	} else if ((sSuffix == "HEU" || sSuffix == "SWZ") && sPath.contains(QString(".adobe/Flash_Player/AssetCache").toUpper())) {
		return "Cache";
	}
	return "Unknown";
}
