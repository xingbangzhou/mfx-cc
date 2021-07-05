TEMPLATE = app
TARGET = pclient

ROOT = ../..
include($$ROOT/include/common.pri)

LIBS += lepluginframework.lib lecore.lib

CONFIG += qt console

QT += widgets

PRECOMPILED_HEADER = stable.h
HEADERS += stable.h \
    lemainframe.h

SOURCES += \
    lemainframe.cpp \
    mian.cpp
