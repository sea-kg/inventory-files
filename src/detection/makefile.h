#ifndef DETECTION_MAKEFILE_H
#define DETECTION_MAKEFILE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionMakefile : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_MAKEFILE_H
