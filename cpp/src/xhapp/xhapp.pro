TEMPLATE = app
TARGET = xhapp

ROOT = ../..
include($$ROOT/include/common.pri)

LIBS += xhpluginframework.lib xhcore.lib

CONFIG += qt console

QT += widgets

PRECOMPILED_HEADER = stable.h
HEADERS += stable.h \
    xhmainframe.h

SOURCES += \
    xhmainframe.cpp \
    mian.cpp
