#ifndef DETECTTYPE_H
#define DETECTTYPE_H


#include <QFileInfo>

QStringList fileTypes();

QString detectType(QFileInfo &file);

#endif // DETECTTYPE_H
