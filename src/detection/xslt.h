#ifndef DETECTION_XSLT_H
#define DETECTION_XSLT_H

#include <QFileInfo>
#include "idetection.h"

class DetectionXSLT : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_XSLT_H
