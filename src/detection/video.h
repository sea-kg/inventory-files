#ifndef DETECTION_VIDEO_H
#define DETECTION_VIDEO_H

#include <QFileInfo>
#include "idetection.h"

class DetectionVideo : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_VIDEO_H
