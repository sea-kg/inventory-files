#ifndef DETECTION_SOURCECODECPP_H
#define DETECTION_SOURCECODECPP_H

#include <QFileInfo>
#include "idetection.h"

class DetectionSourceCodeCpp : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_SOURCECODECPP_H
