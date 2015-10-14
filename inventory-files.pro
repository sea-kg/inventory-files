QT += core
QT += gui
QT += widgets
QT += sql

TARGET = inventory-files.bin
CONFIG += console release
TEMPLATE = app
SOURCES += \
	src/directorymodel.cpp \
	src/jobsmodel.cpp \
	src/job.cpp \
	src/mainwindow.cpp \
	src/main.cpp \
	src/detection/animation.cpp	\
	src/detection/application.cpp \
	src/detection/archiv.cpp \
	src/detection/cache.cpp \
	src/detection/config.cpp \
	src/detection/css.cpp \
	src/detection/document.cpp \
	src/detection/gimp.cpp \
	src/detection/image.cpp \
	src/detection/javascript.cpp \
	src/detection/library.cpp \
	src/detection/logfile.cpp \
	src/detection/presentation.cpp \
	src/detection/python.cpp \
	src/detection/sound.cpp \
	src/detection/sourcecodecpp.cpp \
	src/detection/text.cpp \
	src/detection/video.cpp \
	src/detection/virtual_machine.cpp \
	src/detection/webpage.cpp \
	src/detection/xml.cpp \
	src/detection/detection.cpp	\

HEADERS += \
	src/directorymodel.h \
	src/jobsmodel.h \
	src/job.h \
	src/mainwindow.h \
	src/detection/idetection.h \
	src/detection/animation.h \
	src/detection/application.h \
	src/detection/archiv.h \
	src/detection/cache.h \
	src/detection/config.h \
	src/detection/css.h \
	src/detection/document.h \
	src/detection/gimp.h \
	src/detection/image.h \
	src/detection/javascript.h \
	src/detection/library.h \
	src/detection/logfile.h \
	src/detection/presentation.h \
	src/detection/python.h \
	src/detection/sound.h \
	src/detection/sourcecodecpp.h \
	src/detection/text.h \
	src/detection/video.h \
	src/detection/virtual_machine.h \
	src/detection/webpage.h \
	src/detection/xml.h \
	src/detection/detection.h \
	

OBJECTS_DIR = tmp/
MOC_DIR = tmp/
