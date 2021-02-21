#ifndef DETECTION_JSON_H
#define DETECTION_JSON_H

#include <QFileInfo>
#include "idetection.h"

class DetectionJson : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_JSON_H
