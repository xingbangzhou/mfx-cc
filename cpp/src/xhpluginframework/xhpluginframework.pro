TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)
DEPENDPATH += $$ROOT/include/xhpluginframework
VPATH += $$ROOT/include/xhpluginframework

QMAKE_CFLAGS += -wd4100
QMAKE_CXXFLAGS += -wd4100

QT -= gui
CONFIG += qt

LIBS += xhcore.lib

DEFINES += XHPLUGINFW_IMPL

PRECOMPILED_HEADER = stable.h
HEADERS += \
        xhpluginframeworklisteners.h \
        xhserviceevent.h \
        xhservicereference_p.h \
        xhserviceregistration.h \
        xhserviceregistration_p.h \
        xhservices.h \
        xhserviceslotentry.h \
        stable.h \
        xhplugin_p.h \
        xhpluginframework_p.h \
        xhpluginframeworkcontext.h \
        xhpluginfwexport.h \
        xhpluginfw_global.h \
        xhplugin_constants.h \
        xhplugin.h \
        xhpluginactivator.h \
        xhplugincontext.h \
        xhplugincontext_p.h \
        xhpluginframework.h \
        xhpluginframeworkfactory.h \
        xhplugins.h \
        xhservicereference.h

SOURCES += \
        xhplugin.cpp \
        xhplugin_p.cpp \
        xhplugincontext.cpp \
        xhpluginframework.cpp \
        xhpluginframework_p.cpp \
        xhpluginframeworkcontext.cpp \
        xhpluginframeworkfactory.cpp \
        xhplugin_constants.cpp \
        xhpluginframeworklisteners.cpp \
        xhplugins.cpp \
        xhserviceevent.cpp \
        xhservicereference_p.cpp \
        xhserviceregistration.cpp \
        xhserviceregistration_p.cpp \
        xhservices.cpp \
        xhserviceslotentry.cpp \
        xhservicereference.cpp
