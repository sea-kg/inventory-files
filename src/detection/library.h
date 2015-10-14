#ifndef DETECTION_LIBRARY_H
#define DETECTION_LIBRARY_H

#include <QFileInfo>
#include "idetection.h"

class DetectionLibrary : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_LIBRARY_H
