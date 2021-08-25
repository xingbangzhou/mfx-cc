TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)
DEPENDPATH += $$ROOT/include/xhcore
VPATH += $$ROOT/include/xhcore

QMAKE_CFLAGS += -wd4100
QMAKE_CXXFLAGS += -wd4100

QT -= gui
CONFIG += qt

DEFINES += XHCORE_IMPL

PRECOMPILED_HEADER = stable.h
HEADERS += \
        stable.h \
        xhcoreexport.h \
        xhlogger.h

SOURCES += \
        xhlogger.cpp
