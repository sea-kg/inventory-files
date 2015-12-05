#ifndef DETECTION_MANUAL_H
#define DETECTION_MANUAL_H

#include <QFileInfo>
#include "idetection.h"

class DetectionManual : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_MANUAL_H
