#ifndef DETECTION_PLAYLIST_H
#define DETECTION_PLAYLIST_H

#include <QFileInfo>
#include "idetection.h"

class DetectionPlayList : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_PLAYLIST_H
