#include "detection.h"
#include "src/detection/animation.h"
#include "src/detection/application.h"
#include "src/detection/archiv.h"
#include "src/detection/cache.h"
#include "src/detection/config.h"
#include "src/detection/css.h"
#include "src/detection/document.h"
#include "src/detection/gimp.h"
#include "src/detection/image.h"
#include "src/detection/javascript.h"
#include "src/detection/library.h"
#include "src/detection/logfile.h"
#include "src/detection/presentation.h"
#include "src/detection/python.h"
#include "src/detection/sound.h"
#include "src/detection/sourcecodecpp.h"
#include "src/detection/text.h"
#include "src/detection/video.h"
#include "src/detection/virtual_machine.h"
#include "src/detection/webpage.h"
#include "src/detection/xml.h"
#include <iostream>

Detection::Detection() {
	m_pDetections.push_back((IDetection *)(new DetectionAnimation()));
	m_pDetections.push_back((IDetection *)(new DetectionApplication()));
	m_pDetections.push_back((IDetection *)(new DetectionArchiv()));
	m_pDetections.push_back((IDetection *)(new DetectionCache()));
	m_pDetections.push_back((IDetection *)(new DetectionConfig()));
	m_pDetections.push_back((IDetection *)(new DetectionCSS()));
	m_pDetections.push_back((IDetection *)(new DetectionDocument()));
	m_pDetections.push_back((IDetection *)(new DetectionGimp()));
	m_pDetections.push_back((IDetection *)(new DetectionImage()));
	m_pDetections.push_back((IDetection *)(new DetectionJavaScript()));
	m_pDetections.push_back((IDetection *)(new DetectionLibrary()));
	m_pDetections.push_back((IDetection *)(new DetectionLogFile()));
	m_pDetections.push_back((IDetection *)(new DetectionPresentation()));
	m_pDetections.push_back((IDetection *)(new DetectionPython()));
	m_pDetections.push_back((IDetection *)(new DetectionSound()));
	m_pDetections.push_back((IDetection *)(new DetectionSourceCodeCpp()));
	m_pDetections.push_back((IDetection *)(new DetectionText()));
	m_pDetections.push_back((IDetection *)(new DetectionVideo()));
	m_pDetections.push_back((IDetection *)(new DetectionVirtualMachine()));
	m_pDetections.push_back((IDetection *)(new DetectionWebPage()));
	m_pDetections.push_back((IDetection *)(new DetectionXML()));
}

// -------------------------------------------------------------------

void Detection::types(QStringList &list) {
	for (int i = 0; i < m_pDetections.size(); i++) {
		m_pDetections[i]->types(list);
	}
	list << "Unknown";
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
