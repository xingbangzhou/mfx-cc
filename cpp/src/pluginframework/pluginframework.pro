TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)

DEPENDPATH += $$ROOT/include/pluginframework
VPATH += $$ROOT/include/pluginframework

CONFIG += qt

DEFINES += PLUGINFRAMEWORK_IMPL

PRECOMPILED_HEADER = stable.h
HEADERS += \
        stable.h \
        uupluginframeworkcontext_p.h \
        uupluginfw_global.h \
        uuplugin.h \
        uuplugincontext.h \
        uupluginframework.h \
        uupluginframeworkfactory.h \
        uuplugins_p.h

SOURCES += \
        uuplugin.cpp \
        uuplugincontext.cpp \
        uupluginframework.cpp \
        uupluginframeworkcontext_p.cpp \
        uupluginframeworkfactory.cpp \
        uuplugins_p.cpp
