#ifndef DETECTION_VIRTUAL_MACHINE_H
#define DETECTION_VIRTUAL_MACHINE_H

#include <QFileInfo>
#include "idetection.h"

class DetectionVirtualMachine : IDetection {
	private:
		QString m_sType;
	public:
		DetectionVirtualMachine();
		virtual void types(QStringList &list);
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype);
};

#endif // DETECTION_VIRTUAL_MACHINE_H
