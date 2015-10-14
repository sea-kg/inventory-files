#ifndef DETECTION_CONFIG_H
#define DETECTION_CONFIG_H

#include <QFileInfo>
#include "idetection.h"

class DetectionConfig : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_CONFIG_H
