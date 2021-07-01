TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)

QMAKE_CFLAGS += -wd4100
QMAKE_CXXFLAGS += -wd4100

DEPENDPATH += $$ROOT/include/pluginframework
VPATH += $$ROOT/include/pluginframework

QT -= gui

CONFIG += qt

DEFINES += UUPLUGINFW_IMPL

PRECOMPILED_HEADER = stable.h
HEADERS += \
        stable.h \
        uuplugin_p.h \
        uupluginframework_p.h \
        uupluginframeworkcontext.h \
        uupluginfwexport.h \
        uuplugin_global.h \
        uuplugin_constants.h \
        uuplugin.h \
        uupluginactivator.h \
        uuplugincontext.h \
        uuplugincontext_p.h \
        uupluginframework.h \
        uupluginframeworkfactory.h \
        uuplugins.h

SOURCES += \
        uuplugin.cpp \
        uuplugin_p.cpp \
        uuplugincontext.cpp \
        uupluginframework.cpp \
        uupluginframework_p.cpp \
        uupluginframeworkcontext.cpp \
        uupluginframeworkfactory.cpp \
        uuplugin_constants.cpp \
        uuplugins.cpp
