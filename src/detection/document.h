#ifndef DETECTION_DOCUMENT_H
#define DETECTION_DOCUMENT_H

#include <QFileInfo>
#include "idetection.h"

class DetectionDocument : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_DOCUMENT_H
