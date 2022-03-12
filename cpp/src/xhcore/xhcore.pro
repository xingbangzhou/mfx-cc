TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)
INCLUDEPATH += $$ROOT/include/xhcore
DEPENDPATH += $$ROOT/include/xhcore
VPATH += $$ROOT/include/xhcore

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
