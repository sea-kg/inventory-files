#ifndef DETECTION_DISKIMAGE_H
#define DETECTION_DISKIMAGE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionDiskImage : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_DISKIMAGE_H
