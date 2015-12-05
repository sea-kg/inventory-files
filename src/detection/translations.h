#ifndef DETECTION_TRANSLATIONS_H
#define DETECTION_TRANSLATIONS_H

#include <QFileInfo>
#include "idetection.h"

class DetectionTranslations : IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_TRANSLATIONS_H
