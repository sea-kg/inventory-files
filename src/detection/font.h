#ifndef DETECTION_FONT_H
#define DETECTION_FONT_H

#include <QFileInfo>
#include "idetection.h"

class DetectionFont : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_FONT_H
