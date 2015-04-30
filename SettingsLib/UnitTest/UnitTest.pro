#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T20:52:56
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_unittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_unittest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../release/ -lsettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../debug/ -lsettings
else:unix: LIBS += -L$$PWD/../ -lsettings

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
