#ifndef DETECTION_DIA_H
#define DETECTION_DIA_H

#include <QFileInfo>
#include "idetection.h"

class DetectionDia : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_DIA_H
