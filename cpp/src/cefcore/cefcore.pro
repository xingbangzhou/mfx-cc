TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)
include($$ROOT/include/cef.pri)

DEPENDPATH += $$ROOT/include/cefcore
VPATH += $$ROOT/include/cefcore

LIBS += d3d11.lib glu32.lib imm32.lib opengl32.lib

CONFIG += qt warn_off

DEFINES += CEFCORE_IMPL

PRECOMPILED_HEADER = stable.h
HEADERS += \
    stable.h \
    cefcore_global.h \
    cefframework.h \
    cefmessageloopex.h

HEADERS += \
    cefframework_p.h \
    switches.h \
    cefappbase.h \
    messageloop.h \
    messageloopex.h \
    browser/cefappbrowser.h \
    browser/messageloopstd.h \
    browser/messageloopexternalpump.h \
    browser/messageloopmultithreaded.h \
    browser/rootwindow.h \
    browser/rootwindowmanager.h \
    render/cefapprender.h

SOURCES += \
    cefframework.cpp \
    cefframework_p.cpp \
    switches.cpp \
    messageloopex.cpp \
    browser/cefappbrowser.cpp \
    browser/messageloopstd.cpp \
    browser/messageloopexternalpump.cpp \
    browser/messageloopmultithreaded.cpp \
    browser/rootwindow.cpp \
    browser/rootwindowmanager.cpp \
    render/cefapprender.cpp
