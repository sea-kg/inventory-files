#ifndef DETECTION_BACKUP_H
#define DETECTION_BACKUP_H

#include <QFileInfo>
#include "idetection.h"

class DetectionBackup : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_BACKUP_H
