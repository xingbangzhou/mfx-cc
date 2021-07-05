TEMPLATE = subdirs

DEPENDPATH += .
INCLUDEPATH += .

SUBDIRS = \
        src/lecore \
	src/lepluginframework \
	src/leplugins \
	src/leclient

lepluginframework.depends = lecore
leclient.depends = lepluginframework

DESTDIR = ../shadow
