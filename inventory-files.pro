QT += core gui widgets

TARGET = inventory-files.bin
CONFIG += console release
TEMPLATE = app
SOURCES += \
	src/mainwidget.cpp \
	src/main.cpp

HEADERS += \
	src/mainwidget.h

OBJECTS_DIR = tmp/
MOC_DIR = tmp/
