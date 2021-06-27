TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)

DEPENDPATH += $$ROOT/include/pluginframework
VPATH += $$ROOT/include/pluginframework

CONFIG += qt

DEFINES += UUPLUGINFW_IMPL

PRECOMPILED_HEADER = stable.h
HEADERS += \
        stable.h \
        uuplugin_p.h \
        uuplugincontext_p.h \
        uupluginfwexport.h \
        uupluginframeworkcontext_p.h \
        uupluginfw_global.h \
        uuplugin.h \
        uupluginactivator.h \
        uuplugincontext.h \
        uupluginframework.h \
        uupluginframeworkfactory.h \
        uuplugins_p.h

SOURCES += \
        uuplugin.cpp \
        uuplugin_p.cpp \
        uuplugincontext.cpp \
        uuplugincontext_p.cpp \
        uupluginframework.cpp \
        uupluginframeworkcontext_p.cpp \
        uupluginframeworkfactory.cpp \
        uuplugins_p.cpp
