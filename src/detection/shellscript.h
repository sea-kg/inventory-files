#ifndef DETECTION_SHELLSCRIPT_H
#define DETECTION_SHELLSCRIPT_H

#include <QFileInfo>
#include "idetection.h"

class DetectionShellScript : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_SHELLSCRIPT_H
