#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T01:01:57
#
#-------------------------------------------------

QT       -= core gui

TARGET = servicemananger
TEMPLATE = lib

DEFINES += SERVICE_MANANGER_LIBRARY

SOURCES += servicemananger.cpp

HEADERS += servicemananger.h

QMAKE_CXXFLAGS += -std=c++11

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SettingsLib/libsettings.so -lsettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SettingsLib/libsettings.so -lsettings
else:unix: LIBS += -L$$PWD/../SettingsLib/libsettings.so -lsettings

INCLUDEPATH += $$PWD/../SettingsLib
DEPENDPATH += $$PWD/../SettingsLib
