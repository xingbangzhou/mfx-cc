DEFINES += USING_CEF_SHARED
QMAKE_CFLAGS += -wd4100
QMAKE_CXXFLAGS += -wd4100
QMAKE_LIBDIR += ../../../depends/cef-85/lib/release
INCLUDEPATH += ../../../depends/cef-85/src
DEPENDPATH = ../../../depends/cef-85/src
VPATH = ../../../depends/cef-85/src

LIBS += libcef.lib
LIBS += libcef_dll_wrapper.lib
