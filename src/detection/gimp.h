#ifndef DETECTION_GIMP_H
#define DETECTION_GIMP_H

#include <QFileInfo>
#include "idetection.h"

class DetectionGimp : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_GIMP_H
