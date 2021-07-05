TEMPLATE = lib
DEFINES += ORG_UU_KAFKA_LIBRARY

ROOT = ../../..
include($$ROOT/include/common.pri)

QT -= gui

CONFIG += qt

LIBS += lepluginframework.lib

PRECOMPILED_HEADER = stable.h
HEADERS += \
    pluginaactivator.h \
    pluginaservice.h \
    stable.h

SOURCES += \
    pluginaactivator.cpp \
    pluginaservice.cpp
