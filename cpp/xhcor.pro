TEMPLATE = subdirs

DEPENDPATH += .
INCLUDEPATH += .

SUBDIRS = \
	src/xhcore \
	src/xhpluginframework \
	src/xhplugins \
	src/xhapp

xhpluginframework.depends = xhcore
xhapp.depends = xhpluginframework

DESTDIR = ../shadow
