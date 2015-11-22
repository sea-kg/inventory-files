#ifndef DETECTION_DIRECTDRAW_H
#define DETECTION_DIRECTDRAW_H

#include <QFileInfo>
#include "idetection.h"

class DetectionDirectDraw : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_DIRECTDRAW_H
