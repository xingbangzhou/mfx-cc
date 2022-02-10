TEMPLATE = subdirs

DEPENDPATH += .
INCLUDEPATH += .

SUBDIRS = \
	src/xhcore \
	src/xhpluginframework \
	src/xhplugins \
	src/examples

xhpluginframework.depends = xhcore

DESTDIR = ../shadow
