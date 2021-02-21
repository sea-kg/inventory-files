#ifndef DETECTION_PROJECT_H
#define DETECTION_PROJECT_H

#include <QFileInfo>
#include "idetection.h"

class DetectionProject : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_PROJECT_H
