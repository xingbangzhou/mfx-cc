TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)
DEPENDPATH += $$ROOT/include/lecore
VPATH += $$ROOT/include/lecore

QMAKE_CFLAGS += -wd4100
QMAKE_CXXFLAGS += -wd4100

QT -= gui
CONFIG += qt

DEFINES += LECORE_IMPL

PRECOMPILED_HEADER = stable.h
HEADERS += \
        stable.h \
        lecoreexport.h \
        lelogger.h

SOURCES += \
        lelogger.cpp
