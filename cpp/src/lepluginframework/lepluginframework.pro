TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)
DEPENDPATH += $$ROOT/include/lepluginframework
VPATH += $$ROOT/include/lepluginframework

QMAKE_CFLAGS += -wd4100
QMAKE_CXXFLAGS += -wd4100

QT -= gui
CONFIG += qt

DEFINES += LEPLUGINFW_IMPL

PRECOMPILED_HEADER = stable.h
HEADERS += \
        lepluginframeworklisteners.h \
        leserviceevent.h \
        leservicereference_p.h \
        leserviceregistration.h \
        leserviceregistration_p.h \
        leservices.h \
        leserviceslotentry.h \
        stable.h \
        leplugin_p.h \
        lepluginframework_p.h \
        lepluginframeworkcontext.h \
        lepluginfwexport.h \
        lepluginfw_global.h \
        leplugin_constants.h \
        leplugin.h \
        lepluginactivator.h \
        leplugincontext.h \
        leplugincontext_p.h \
        lepluginframework.h \
        lepluginframeworkfactory.h \
        leplugins.h \
        leservicereference.h

SOURCES += \
        leplugin.cpp \
        leplugin_p.cpp \
        leplugincontext.cpp \
        lepluginframework.cpp \
        lepluginframework_p.cpp \
        lepluginframeworkcontext.cpp \
        lepluginframeworkfactory.cpp \
        leplugin_constants.cpp \
        lepluginframeworklisteners.cpp \
        leplugins.cpp \
        leserviceevent.cpp \
        leservicereference_p.cpp \
        leserviceregistration.cpp \
        leserviceregistration_p.cpp \
        leservices.cpp \
        leserviceslotentry.cpp \
        leservicereference.cpp
