#ifndef DETECTION_XML_H
#define DETECTION_XML_H

#include <QFileInfo>
#include "idetection.h"

class DetectionXML : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_XML_H
