#ifndef DETECTION_SETUP_H
#define DETECTION_SETUP_H

#include <QFileInfo>
#include "idetection.h"

class DetectionSetup : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_SETUP_H
