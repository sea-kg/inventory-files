#ifndef DETECTION_TORRENT_H
#define DETECTION_TORRENT_H

#include <QFileInfo>
#include "idetection.h"

class DetectionTorrent : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_TORRENT_H
