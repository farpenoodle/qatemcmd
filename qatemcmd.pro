#-------------------------------------------------
#
# Project created by QtCreator 2014-08-04T15:03:09
#
#-------------------------------------------------

QT       += core network

#QT       -= gui

TARGET = qatemcmd
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    libqatemcontrol/qatemconnection.cpp \
    qatemcontroller.cpp

HEADERS += \
    libqatemcontrol/libqatemcontrol_global.h \
    libqatemcontrol/qatemconnection.h \
    libqatemcontrol/qdownstreamkeysettings.h \
    libqatemcontrol/qupstreamkeysettings.h \
    qatemcontroller.h
