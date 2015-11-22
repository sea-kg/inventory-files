#ifndef DETECTION_BATCHFILE_H
#define DETECTION_BATCHFILE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionBatchFile : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_BATCHFILE_H
