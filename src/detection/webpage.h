#ifndef DETECTION_WEBPAGE_H
#define DETECTION_WEBPAGE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionWebPage : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_WEBPAGE_H
