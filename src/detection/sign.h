#ifndef DETECTION_SIGN_H
#define DETECTION_SIGN_H

#include <QFileInfo>
#include "idetection.h"

class DetectionSign : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_SIGN_H
