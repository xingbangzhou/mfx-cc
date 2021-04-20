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
HEADERS += stable.h \
    cefappbase.h \
	cefframework.h \
	cefframework_p.h \
	switches.h \
    browser/cefappbrowser.h \
	render/cefapprender.h

SOURCES += \
    cefappbase.cpp \
	cefframework.cpp \
	cefframework_p.cpp \
	switches.cpp \
    browser/cefappbrowser.cpp \
	render/cefapprender.cpp
