#ifndef DETECTION_LINK_H
#define DETECTION_LINK_H

#include <QFileInfo>
#include "idetection.h"

class DetectionLink : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_LINK_H
