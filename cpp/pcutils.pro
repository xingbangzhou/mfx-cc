TEMPLATE = subdirs

DEPENDPATH += .
INCLUDEPATH += .

SUBDIRS = \
    src/libcef_dll_wrapper \
	src/cefcore \
	src/pclient

cefcore.depends = libcef_dll_wrapper
pclient.depends = cefcore

DESTDIR = ../shadow