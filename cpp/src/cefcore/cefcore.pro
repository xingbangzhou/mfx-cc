TEMPLATE = lib

ROOT = ../..
include($$ROOT/include/common.pri)
include($$ROOT/include/cef.pri)

LIBS += d3d11.lib glu32.lib imm32.lib opengl32.lib

CONFIG += qt warn_off

DEFINES += CEFCORE_IMPL

PRECOMPILED_HEADER = stable.h
HEADERS += stable.h \
    cefappbrowser.h \
    cefframework.h

SOURCES += \
    cefappbrowser.cpp \
    cefframework.cpp
