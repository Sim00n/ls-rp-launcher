#-------------------------------------------------
#
# Project created by QtCreator 2013-04-08T21:39:18
#
#-------------------------------------------------

QT       += core

QT       -= gui
QT       += network

TARGET = WebFiles
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    remotefiles.cpp \
    localfiles.cpp

HEADERS += \
    remotefiles.h \
    localfiles.h
