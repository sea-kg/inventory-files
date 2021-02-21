#ifndef DETECTION_BINARY_DIFF_H
#define DETECTION_BINARY_DIFF_H

#include <QFileInfo>
#include "idetection.h"

class DetectionBinaryDiff : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_BINARY_DIFF_H
