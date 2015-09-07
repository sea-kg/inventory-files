#include "mainwidget.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QFileInfo>
#include <qmath.h>
#include <iostream>
#include <QApplication>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Inventory-files"));

}
