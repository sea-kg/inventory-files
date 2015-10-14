#ifndef IDETECTION_H
#define IDETECTION_H

#include <QFileInfo>
#include <QString>
#include <QStringList>

class IDetection {
	public:
		virtual void types(QStringList &list) = 0;
		virtual bool isType(const QFileInfo &fi, QString &type, QString &subtype) = 0;
};

#endif // IDETECTION_H
