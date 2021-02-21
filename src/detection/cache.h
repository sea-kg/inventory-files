#ifndef DETECTION_CACHE_H
#define DETECTION_CACHE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionCache : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_CACHE_H
