QT += core
QT += gui
QT += widgets
QT += sql

INCLUDEPATH += 3rdparty/clucene/src/core/
INCLUDEPATH += 3rdparty/clucene/src/core/CLucene/

TARGET = inventory-files.bin
CONFIG += console release
TEMPLATE = app
SOURCES += \
	src/qsimplenopesql/qsimplenopesql.cpp \
	src/qsimplenopesql/qsimplenopesql_doc.cpp \
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
	src/detection/dia.cpp \
	src/detection/document.cpp \
	src/detection/font.cpp \
	src/detection/gimp.cpp \
	src/detection/image.cpp \
	src/detection/javascript.cpp \
	src/detection/json.cpp \
	src/detection/library.cpp \
	src/detection/logfile.cpp \
	src/detection/makefile.cpp \
	src/detection/mercurial.cpp \
	src/detection/php.cpp \
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
	src/qsimplenopesql/qsimplenopesql.h \
	src/qsimplenopesql/qsimplenopesql_doc.h \
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
	src/detection/dia.h \
	src/detection/document.h \
	src/detection/font.h \
	src/detection/gimp.h \
	src/detection/image.h \
	src/detection/javascript.h \
	src/detection/json.h \
	src/detection/library.h \
	src/detection/logfile.h \
	src/detection/makefile.h \
	src/detection/mercurial.h \
	src/detection/php.h \
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
