#ifndef DETECTION_JAVASCRIPT_H
#define DETECTION_JAVASCRIPT_H

#include <QFileInfo>
#include "idetection.h"

class DetectionJavaScript : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_JAVASCRIPT_H
