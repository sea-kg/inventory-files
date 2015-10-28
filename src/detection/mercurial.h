#ifndef DETECTION_MERCURIAL_H
#define DETECTION_MERCURIAL_H

#include <QFileInfo>
#include "idetection.h"

class DetectionMercurial : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_MERCURIAL_H
