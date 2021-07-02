TEMPLATE = subdirs

DEPENDPATH += .
INCLUDEPATH += .

SUBDIRS = \
        src/lecore \
	src/lepluginframework \
	src/leplugins \
	src/leclient

leclient.depends = lepluginframework

DESTDIR = ../shadow
