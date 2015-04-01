#-------------------------------------------------
#
# Project created by QtCreator 2015-03-16T22:16:11
#
#-------------------------------------------------

QT       -= core gui

TARGET = Settings
TEMPLATE = lib

DEFINES += SETTINGS_LIBRARY

SOURCES += settings.cpp

HEADERS += settings.h

QMAKE_CXXFLAGS += -std=c++11 -fpermissive

unix {
    target.path = /usr/lib
    INSTALLS += target
}
