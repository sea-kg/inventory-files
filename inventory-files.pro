QT += core gui widgets
QT += gui
QT += widgets
QT += sql

TARGET = inventory-files.bin
CONFIG += console release
TEMPLATE = app
SOURCES += \
	src/directorymodel.cpp \
	src/mainwindow.cpp \
	src/main.cpp

HEADERS += \
	src/directorymodel.h \
	src/mainwindow.h

OBJECTS_DIR = tmp/
MOC_DIR = tmp/
