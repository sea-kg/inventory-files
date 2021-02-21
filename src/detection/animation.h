#ifndef DETECTION_ANIMATION_H
#define DETECTION_ANIMATION_H

#include <QFileInfo>
#include "idetection.h"

class DetectionAnimation : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_ANIMATION_H
