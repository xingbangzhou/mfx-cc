TEMPLATE = lib
DEFINES += ORG_UU_KAFKA_LIBRARY

ROOT = ../../..
include($$ROOT/include/common.pri)

QT -= gui

CONFIG += qt

LIBS += pluginframework.lib

PRECOMPILED_HEADER = stable.h
HEADERS += \
    stable.h \
    pluginkafkaactivator.h

SOURCES += \
    pluginkafkaactivator.cpp
