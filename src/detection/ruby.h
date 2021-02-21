#ifndef DETECTION_RUBY_H
#define DETECTION_RUBY_H

#include <QFileInfo>
#include "idetection.h"

class DetectionRuby : public IDetection {
	public:
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_RUBY_H
