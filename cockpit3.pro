#-------------------------------------------------
#
# Project created by QtCreator 2014-05-20T20:52:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cockpit3
TEMPLATE = app


SOURCES += main.cpp\
        settings.cpp \
    instrument_panel.cpp \
    gamestate.cpp \
    cockpit.cpp \
    flapsindicator.cpp \
    genericindicator.cpp \
    editor.cpp \
    variometer.cpp \
    mapindicator.cpp \
    targetdistanceindicator.cpp \
    aviahorizonindicator.cpp \
    angletotargetindicator.cpp

HEADERS  += settings.h \
    instrument_panel.h \
    gamestate.h \
    cockpit.h \
    flapsindicator.h \
    genericindicator.h \
    editor.h \
    variometer.h \
    mapindicator.h \
    targetdistanceindicator.h \
    aviahorizonindicator.h \
    angletotargetindicator.h

CONFIG += openssl-linked
MOBILITY = 


OTHER_FILES += \
    settings.json \
    images/flaps.png \
    images/vario.png \
    images/vario_needle.png \
    android/AndroidManifest.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android



