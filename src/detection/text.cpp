#include "text.h"

void DetectionText::types(QStringList &list) {
	list << "Text";
}

// --------------------------------------------------------------------

bool DetectionText::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "TXT" || sSuffix == "SRT" || sSuffix == "LSM" || sSuffix == "NSI"
		|| sSuffix == "M4"
		|| sSuffix == "DIFF"
		|| sSuffix == "SPEC"
		|| sSuffix == "FILES"
		|| sSuffix == "CHANGES"
		|| sSuffix == "MD5SUM"
		|| sSuffix == "NEWS"
		|| sSuffix == "BOT"
		|| sName == "TODO"
		|| sName == "NEWS"
		|| sName == "README"
		|| sName == "INSTALL"
		|| sName == "COPYING"
		|| sName == "COPYING-DOCS"
		|| sName == "AUTHORS"
		|| sName == "CHANGELOG"
		|| sName == "SUBDIRS"
		|| sName == "CPP"
		|| sName == "H"
		|| sName == "FLAGS_LICENCE"
	);
	if (bType) {
		type = "Text";
		subtype = "todo"; // version and another information
		if(sSuffix == "LSM"){
			subtype = "Linux Software Map"; // need look inside file maybe it image not text
		}else if(sSuffix == "NSI"){
			subtype = "NSIS Script File";
		}else if(sSuffix == "M4"){
			subtype = "m4 (computer language)";
		}else if(sName == "CHANGELOG"){
			subtype = "Change Log";
		}else if(sSuffix == "DIFF"){
			subtype = "Diff";
		}
	}
	return bType;
}
