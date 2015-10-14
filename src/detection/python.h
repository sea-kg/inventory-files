#ifndef DETECTION_PYTHON_H
#define DETECTION_PYTHON_H

#include <QFileInfo>
#include "idetection.h"

class DetectionPython : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_PYTHON_H
