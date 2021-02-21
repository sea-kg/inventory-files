#ifndef DETECTION_TEXT_H
#define DETECTION_TEXT_H

#include <QFileInfo>
#include "idetection.h"

class DetectionText : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_TEXT_H
