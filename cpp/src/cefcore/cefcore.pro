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
HEADERS += stable.h cefcore_global.h

HEADERS += cefframework.h cefframework_p.h
SOURCES += cefframework.cpp cefframework_p.cpp

HEADERS += switches.h
SOURCES += switches.cpp

HEADERS += \
        cefappbase.h \
        cefmsgloophelp.h \
		cefmessageloop.h \
        browser/cefappbrowser.h \
        browser/messageloopmultithreaded.h \
        browser/messageloopexternalpump.h \
        browser/messageloopstd.h

SOURCES += \        
        browser/cefappbrowser.cpp \
        browser/messageloopmultithreaded.cpp \
        browser/messageloopexternalpump.cpp \
        browser/messageloopstd.cpp

HEADERS += \
        render/cefapprender.h

SOURCES += \
        render/cefapprender.cpp
