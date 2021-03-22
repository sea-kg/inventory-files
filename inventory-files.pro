QT += core
QT += gui
QT += widgets
QT += sql

INCLUDEPATH += $$PWD/src/interfaces

TARGET = inventory-files
CONFIG += console release
TEMPLATE = app
SOURCES += \
    src/directorymodel.cpp \
    src/jobsmodel.cpp \
    src/job.cpp \
    src/scandialog.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/detection/animation.cpp    \
    src/detection/application.cpp \
    src/detection/archiv.cpp \
    src/detection/backup.cpp \
    src/detection/batchfile.cpp \
    src/detection/binarydata.cpp \
    src/detection/binary_diff.cpp \
    src/detection/cache.cpp \
    src/detection/config.cpp \
    src/detection/css.cpp \
    src/detection/cvs.cpp \
    src/detection/dia.cpp \
    src/detection/diskimage.cpp \
    src/detection/directdraw.cpp \
    src/detection/document.cpp \
    src/detection/doxyfile.cpp \
    src/detection/font.cpp \
    src/detection/gimp.cpp \
    src/detection/guitarpro.cpp \
    src/detection/image.cpp \
    src/detection/java_application.cpp \
    src/detection/javascript.cpp \
    src/detection/json.cpp \
    src/detection/library.cpp \
    src/detection/link.cpp \
    src/detection/logfile.cpp \
    src/detection/makefile.cpp \
    src/detection/manual.cpp \
    src/detection/mercurial.cpp \
    src/detection/perl.cpp \
    src/detection/php.cpp \
    src/detection/playlist.cpp \
    src/detection/presentation.cpp \
    src/detection/project.cpp \
    src/detection/python.cpp \
    src/detection/rc.cpp \
    src/detection/ruby.cpp \
    src/detection/setup.cpp \
    src/detection/shellscript.cpp \
    src/detection/sign.cpp \
    src/detection/sound.cpp \
    src/detection/soundforgepeakfile.cpp \
    src/detection/sourcecodecpp.cpp \
    src/detection/text.cpp \
    src/detection/torrent.cpp \
    src/detection/translations.cpp \
    src/detection/ui.cpp \
    src/detection/video.cpp \
    src/detection/virtual_machine.cpp \
    src/detection/webpage.cpp \
    src/detection/xml.cpp \
    src/detection/xslt.cpp \
    src/detection/detection_object_file.cpp \
    src/detection/detection.cpp

HEADERS += \
    src/directorymodel.h \
    src/jobsmodel.h \
    src/job.h \
    src/scandialog.h \
    src/mainwindow.h \
    src/detection/idetection.h \
    src/detection/animation.h \
    src/detection/application.h \
    src/detection/archiv.h \
    src/detection/backup.h \
    src/detection/batchfile.h \
    src/detection/binarydata.h \
    src/detection/binary_diff.h \
    src/detection/cache.h \
    src/detection/config.h \
    src/detection/css.h \
    src/detection/cvs.h \
    src/detection/dia.h \
    src/detection/diskimage.h \
    src/detection/directdraw.h \
    src/detection/document.h \
    src/detection/doxyfile.h \
    src/detection/font.h \
    src/detection/gimp.h \
    src/detection/guitarpro.h \
    src/detection/image.h \
    src/detection/java_application.h \
    src/detection/javascript.h \
    src/detection/json.h \
    src/detection/library.h \
    src/detection/link.h \
    src/detection/logfile.h \
    src/detection/makefile.h \
    src/detection/manual.h \
    src/detection/mercurial.h \
    src/detection/perl.h \
    src/detection/php.h \
    src/detection/playlist.h \
    src/detection/presentation.h \
    src/detection/project.h \
    src/detection/python.h \
    src/detection/rc.h \
    src/detection/ruby.h \
    src/detection/setup.h \
    src/detection/shellscript.h \
    src/detection/sign.h \
    src/detection/sound.h \
    src/detection/soundforgepeakfile.h \
    src/detection/sourcecodecpp.h \
    src/detection/text.h \
    src/detection/torrent.h \
    src/detection/translations.h \
    src/detection/ui.h \
    src/detection/video.h \
    src/detection/virtual_machine.h \
    src/detection/webpage.h \
    src/detection/xml.h \
    src/detection/xslt.h \
    src/detection/detection_object_file.h \
    src/detection/detection.h

RESOURCES     = inventory-files.qrc

OBJECTS_DIR = tmp/
MOC_DIR = tmp/
