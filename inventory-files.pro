QT += core
QT += gui
QT += widgets
QT += sql

TARGET = inventory-files.bin
CONFIG += console release
TEMPLATE = app
SOURCES += \
	src/directorymodel.cpp \
	src/filesmodel.cpp \
	src/job.cpp \
	src/mainwindow.cpp \
	src/main.cpp

HEADERS += \
	src/directorymodel.h \
	src/filesmodel.h \
	src/job.h \
	src/mainwindow.h

OBJECTS_DIR = tmp/
MOC_DIR = tmp/
