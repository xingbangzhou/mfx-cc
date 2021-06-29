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
        uupluginframework_p.h \
        uupluginfwexport.h \
        uupluginframeworkcontext_p.h \
        uupluginfw_global.h \
        uuplugin_constants.h \
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
        uupluginframework.cpp \
        uupluginframework_p.cpp \
        uupluginframeworkcontext_p.cpp \
        uupluginframeworkfactory.cpp \
        uuplugins_p.cpp \
        uuplugin_constants.cpp
