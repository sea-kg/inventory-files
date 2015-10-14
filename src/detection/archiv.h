#ifndef DETECTION_ARCHIV_H
#define DETECTION_ARCHIV_H

#include <QFileInfo>
#include "idetection.h"

class DetectionArchiv : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_ARCHIV_H
