TEMPLATE = app
TARGET = pclient

ROOT = ../..
include($$ROOT/include/common.pri)

CONFIG += qt

QT += widgets

LIBS += cefcore.lib

PRECOMPILED_HEADER = stable.h
HEADERS += stable.h

SOURCES += \
    mian.cpp
