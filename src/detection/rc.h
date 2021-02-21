#ifndef DETECTION_RC_H
#define DETECTION_RC_H

#include <QFileInfo>
#include "idetection.h"

class DetectionRC : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_RC_H
