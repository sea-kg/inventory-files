#ifndef DETECTION_BINARYDATA_H
#define DETECTION_BINARYDATA_H

#include <QFileInfo>
#include "idetection.h"

class DetectionBinaryData : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_BINARYDATA_H
