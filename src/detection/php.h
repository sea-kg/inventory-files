#ifndef DETECTION_PHP_H
#define DETECTION_PHP_H

#include <QFileInfo>
#include "idetection.h"

class DetectionPHP : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_PHP_H
