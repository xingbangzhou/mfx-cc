TEMPLATE = app
TARGET = pclient

ROOT = ../..
include($$ROOT/include/common.pri)

LIBS += lepluginframework.lib

CONFIG += qt console

QT += widgets

PRECOMPILED_HEADER = stable.h
HEADERS += stable.h

SOURCES += \
    mian.cpp
