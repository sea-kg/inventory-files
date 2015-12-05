#ifndef DETECTION_UI_H
#define DETECTION_UI_H

#include <QFileInfo>
#include "idetection.h"

class DetectionUI : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_UI_H
