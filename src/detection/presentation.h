#ifndef DETECTION_PRESENTATION_H
#define DETECTION_PRESENTATION_H

#include <QFileInfo>
#include "idetection.h"

class DetectionPresentation : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_PRESENTATION_H
