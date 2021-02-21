#ifndef DETECTION_LOGFILE_H
#define DETECTION_LOGFILE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionLogFile : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_LOGFILE_H
