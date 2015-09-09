QT += core gui widgets
QT += gui
QT += widgets
QT += sql

TARGET = inventory-files.bin
CONFIG += console release
TEMPLATE = app
SOURCES += \
	src/directorymodel.cpp \
	src/mainwidget.cpp \
	src/main.cpp

HEADERS += \
	src/directorymodel.h \
	src/mainwidget.h

OBJECTS_DIR = tmp/
MOC_DIR = tmp/
