#ifndef DETECTION_DOXYFILE_H
#define DETECTION_DOXYFILE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionDoxyfile : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_DOXYFILE_H
