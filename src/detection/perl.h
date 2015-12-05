#ifndef DETECTION_PERL_H
#define DETECTION_PERL_H

#include <QFileInfo>
#include "idetection.h"

class DetectionPerl : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_PERL_H
