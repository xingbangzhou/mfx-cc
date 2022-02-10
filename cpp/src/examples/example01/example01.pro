TEMPLATE = app
TARGET = example01

ROOT = ../../..
include($$ROOT/include/common.pri)

QT -= gui

CONFIG += c++11 console

DEFINES += QT_DEPRECATED_WARNINGS

PRECOMPILED_HEADER = stable.h
HEADERS += stable.h

SOURCES += \
    mian.cpp
