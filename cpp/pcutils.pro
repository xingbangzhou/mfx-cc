TEMPLATE = subdirs

DEPENDPATH += .
INCLUDEPATH += .

SUBDIRS = \
    src/libcef_dll_wrapper \
	src/cefclient

cefclient.depends = libcef_dll_wrapper