#ifndef DETECTION_SOUND_H
#define DETECTION_SOUND_H

#include <QFileInfo>
#include "idetection.h"

class DetectionSound : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_SOUND_H
