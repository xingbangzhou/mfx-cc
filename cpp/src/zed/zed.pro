TEMPLATE = app
TARGET = zed

ROOT = ../..
include($$ROOT/include/common.pri)

CONFIG += qt

PRECOMPILED_HEADER = stable.h
HEADERS += stable.h

SOURCES += \
    mian.cpp
