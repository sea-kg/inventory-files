#ifndef DETECTION_CVS_H
#define DETECTION_CVS_H

#include <QFileInfo>
#include "idetection.h"

class DetectionCVS : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_CVS_H
