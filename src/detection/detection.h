#ifndef DETECTION_H
#define DETECTION_H

#include <QFileInfo>
#include <QVector>
#include "idetection.h"

class Detection : IDetection {
	private:
		QVector<IDetection *> m_pDetections;
	public:
		Detection();
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_H
