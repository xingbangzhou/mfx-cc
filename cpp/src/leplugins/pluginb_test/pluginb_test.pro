TEMPLATE = lib
DEFINES += ORG_UU_KAFKA_LIBRARY

ROOT = ../../..
include($$ROOT/include/common.pri)

QT -= gui

CONFIG += qt

LIBS += lepluginframework.lib

PRECOMPILED_HEADER = stable.h
HEADERS += \
    pluginbactivator.h \
    pluginbservice.h \
    stable.h

SOURCES += \
    pluginbactivator.cpp \
    pluginbservice.cpp
