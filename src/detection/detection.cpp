#include "detection.h"
#include "src/detection/animation.h"
#include "src/detection/application.h"
#include "src/detection/archiv.h"
#include "src/detection/backup.h"
#include "src/detection/batchfile.h"
#include "src/detection/binarydata.h"
#include "src/detection/binary_diff.h"
#include "src/detection/cache.h"
#include "src/detection/config.h"
#include "src/detection/css.h"
#include "src/detection/cvs.h"
#include "src/detection/dia.h"
#include "src/detection/diskimage.h"
#include "src/detection/directdraw.h"
#include "src/detection/document.h"
#include "src/detection/doxyfile.h"
#include "src/detection/font.h"
#include "src/detection/gimp.h"
#include "src/detection/guitarpro.h"
#include "src/detection/image.h"
#include "src/detection/java_application.h"
#include "src/detection/javascript.h"
#include "src/detection/json.h"
#include "src/detection/library.h"
#include "src/detection/link.h"
#include "src/detection/logfile.h"
#include "src/detection/makefile.h"
#include "src/detection/manual.h"
#include "src/detection/mercurial.h"
#include "src/detection/perl.h"
#include "src/detection/php.h"
#include "src/detection/playlist.h"
#include "src/detection/presentation.h"
#include "src/detection/project.h"
#include "src/detection/python.h"
#include "src/detection/rc.h"
#include "src/detection/ruby.h"
#include "src/detection/setup.h"
#include "src/detection/shellscript.h"
#include "src/detection/sign.h"
#include "src/detection/sound.h"
#include "src/detection/soundforgepeakfile.h"
#include "src/detection/sourcecodecpp.h"
#include "src/detection/text.h"
#include "src/detection/torrent.h"
#include "src/detection/translations.h"
#include "src/detection/ui.h"
#include "src/detection/video.h"
#include "src/detection/virtual_machine.h"
#include "src/detection/webpage.h"
#include "src/detection/xml.h"

#include <iostream>

Detection::Detection() {
	m_pDetections.push_back((IDetection *)(new DetectionAnimation()));
	m_pDetections.push_back((IDetection *)(new DetectionApplication()));
	m_pDetections.push_back((IDetection *)(new DetectionArchiv()));
	m_pDetections.push_back((IDetection *)(new DetectionBackup()));
	m_pDetections.push_back((IDetection *)(new DetectionBatchFile()));
	m_pDetections.push_back((IDetection *)(new DetectionBinaryData()));
	m_pDetections.push_back((IDetection *)(new DetectionBinaryDiff()));
	m_pDetections.push_back((IDetection *)(new DetectionCache()));
	m_pDetections.push_back((IDetection *)(new DetectionConfig()));
	m_pDetections.push_back((IDetection *)(new DetectionCSS()));
	m_pDetections.push_back((IDetection *)(new DetectionCVS()));
	m_pDetections.push_back((IDetection *)(new DetectionDia()));
	m_pDetections.push_back((IDetection *)(new DetectionDiskImage()));
	m_pDetections.push_back((IDetection *)(new DetectionDirectDraw()));
	m_pDetections.push_back((IDetection *)(new DetectionDocument()));
	m_pDetections.push_back((IDetection *)(new DetectionDoxyfile()));
	m_pDetections.push_back((IDetection *)(new DetectionFont()));
	m_pDetections.push_back((IDetection *)(new DetectionGimp()));
	m_pDetections.push_back((IDetection *)(new DetectionGuitarPro()));
	m_pDetections.push_back((IDetection *)(new DetectionImage()));
	m_pDetections.push_back((IDetection *)(new DetectionJavaApplication()));
	m_pDetections.push_back((IDetection *)(new DetectionJavaScript()));
	m_pDetections.push_back((IDetection *)(new DetectionJson()));
	m_pDetections.push_back((IDetection *)(new DetectionLibrary()));
	m_pDetections.push_back((IDetection *)(new DetectionLink()));
	m_pDetections.push_back((IDetection *)(new DetectionLogFile()));
	m_pDetections.push_back((IDetection *)(new DetectionMakefile()));
	m_pDetections.push_back((IDetection *)(new DetectionManual()));
	m_pDetections.push_back((IDetection *)(new DetectionMercurial()));
	m_pDetections.push_back((IDetection *)(new DetectionPerl()));
	m_pDetections.push_back((IDetection *)(new DetectionPHP()));
	m_pDetections.push_back((IDetection *)(new DetectionPlayList()));
	m_pDetections.push_back((IDetection *)(new DetectionPresentation()));
	m_pDetections.push_back((IDetection *)(new DetectionProject()));
	m_pDetections.push_back((IDetection *)(new DetectionPython()));
	m_pDetections.push_back((IDetection *)(new DetectionRC()));
	m_pDetections.push_back((IDetection *)(new DetectionRuby()));
	m_pDetections.push_back((IDetection *)(new DetectionSetup()));
	m_pDetections.push_back((IDetection *)(new DetectionShellScript()));
	m_pDetections.push_back((IDetection *)(new DetectionSign()));
	m_pDetections.push_back((IDetection *)(new DetectionSound()));
	m_pDetections.push_back((IDetection *)(new DetectionSoundForgePeakFile()));
	m_pDetections.push_back((IDetection *)(new DetectionSourceCodeCpp()));
	m_pDetections.push_back((IDetection *)(new DetectionText()));
	m_pDetections.push_back((IDetection *)(new DetectionTorrent()));
	m_pDetections.push_back((IDetection *)(new DetectionTranslations()));
	m_pDetections.push_back((IDetection *)(new DetectionUI()));
	m_pDetections.push_back((IDetection *)(new DetectionVideo()));
	m_pDetections.push_back((IDetection *)(new DetectionVirtualMachine()));
	m_pDetections.push_back((IDetection *)(new DetectionWebPage()));
	m_pDetections.push_back((IDetection *)(new DetectionXML()));
}

// -------------------------------------------------------------------

void Detection::types(QStringList &list) {
	for (int i = 0; i < m_pDetections.size(); i++) {
		QStringList tmpList;
		m_pDetections[i]->types(tmpList);
		for (int i1 = 0; i1 < tmpList.size(); i1++) {
			if (!list.contains(tmpList[i1]))
				list << tmpList[i1];
		}
	}
	QString strUnknown = "Unknown";
	if (!list.contains(strUnknown))
		list << strUnknown;
};

// -------------------------------------------------------------------

bool Detection::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString tmpType = "";
	QString tmpSubType = "";

	bool bType = false;
	for (int i = 0; i < m_pDetections.size(); i++) {
		if (bType == false && m_pDetections[i]->isType(fi, tmpType, tmpSubType)) {
			type = tmpType;
			subtype = tmpSubType;
			bType = true;
		} else if (bType == true && m_pDetections[i]->isType(fi, tmpType, tmpSubType)) {
			// todo exception
			std::cout << "FAIL: Conflict types " << type.toStdString() << " and " << tmpType.toStdString() << "\n";
			return false;
		}
	}
	
	if (bType == false) {
		type = "Unknown";
		subtype = "";
		bType = true;
	}

	return bType;
}

// -------------------------------------------------------------------
