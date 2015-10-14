#ifndef DETECTION_APPLICATION_H
#define DETECTION_APPLICATION_H

#include <QFileInfo>
#include "idetection.h"

class DetectionApplication : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_APPLICATION_H
