TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)
INCLUDEPATH += $$ROOT/include/xhutils
DEPENDPATH += $$ROOT/include/xhutils
VPATH += $$ROOT/include/xhutils

QT += core gui widgets
CONFIG += qt

DEFINES += XHUTILS_IMPL

include(framelesshelper/framelesshelper.pri)
PRECOMPILED_HEADER = stable.h
HEADERS += \
        stable.h \
        xhutilsexport.h
