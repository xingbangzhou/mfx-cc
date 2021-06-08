DEFINES += USING_CEF_SHARED
QMAKE_CFLAGS += -wd4100
QMAKE_CXXFLAGS += -wd4100
QMAKE_LIBDIR += ../../../depends/cef/lib/release
INCLUDEPATH += ../../../depends/cef/src
DEPENDPATH = ../../../depends/cef/src
VPATH = ../../../depends/cef/src

LIBS += libcef.lib
LIBS += libcef_dll_wrapper.lib
