#ifndef DETECTION_CSS_H
#define DETECTION_CSS_H

#include <QFileInfo>
#include "idetection.h"

class DetectionCSS : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_CSS_H
