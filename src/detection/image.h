#ifndef DETECTION_IMAGE_H
#define DETECTION_IMAGE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionImage : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_IMAGE_H
