QT += core
QT += gui
QT += widgets
QT += sql

TARGET = inventory-files.bin
CONFIG += console release
TEMPLATE = app
SOURCES += \
	src/detecttype.cpp \
	src/directorymodel.cpp \
	src/jobsmodel.cpp \
	src/job.cpp \
	src/mainwindow.cpp \
	src/main.cpp

HEADERS += \
	src/detecttype.h \
	src/directorymodel.h \
	src/jobsmodel.h \
	src/job.h \
	src/mainwindow.h

OBJECTS_DIR = tmp/
MOC_DIR = tmp/
