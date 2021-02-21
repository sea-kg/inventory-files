#ifndef DETECTION_OBJECT_FILE_H
#define DETECTION_OBJECT_FILE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionObjectFile : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_OBJECT_FILE_H
