#ifndef DETECTION_UNKNOWN_H
#define DETECTION_UNKNOWN_H

#include <QFileInfo>

class DetectionUnknown {
	public:
		virtual QString type();
		virtual bool isType();
};

#endif // DETECTION_UNKNOWN_H
