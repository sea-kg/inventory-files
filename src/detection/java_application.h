#ifndef DETECTION_JAVA_APPLICATION_H
#define DETECTION_JAVA_APPLICATION_H

#include <QFileInfo>
#include "idetection.h"

class DetectionJavaApplication : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_JAVA_APPLICATION_H
