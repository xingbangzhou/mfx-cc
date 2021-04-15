TEMPLATE = subdirs

DEPENDPATH += .
INCLUDEPATH += .

SUBDIRS = \
    src/libcef_dll_wrapper \
	src/cefcore \
	src/zed \
	src/cefclient

cefcore.depends = libcef_dll_wrapper
zed.depends = cefcore
cefclient.depends = libcef_dll_wrapper