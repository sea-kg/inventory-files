#ifndef DETECTION_GUITARPRO_H
#define DETECTION_GUITARPRO_H

#include <QFileInfo>
#include "idetection.h"

class DetectionGuitarPro : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_GUITARPRO_H
