#ifndef DETECTION_SOUNDFOURGEPEAKFILE_H
#define DETECTION_SOUNDFOURGEPEAKFILE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionSoundForgePeakFile : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_SOUNDFOURGEPEAKFILE_H
