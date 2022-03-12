TEMPLATE = app
TARGET = wink

QT += core gui widgets

ROOT = ../../..
include($$ROOT/include/common.pri)

LIBS += xhcore.lib xhutils.lib

RC_ICONS = logo.ico
RESOURCES += \
    Resource.qrc
	
include(views/views.pri)
include(framework/framework.pri)
include(bizcore/bizcore.pri)

PRECOMPILED_HEADER = stable.h
HEADERS += stable.h

SOURCES += \
    mian.cpp
