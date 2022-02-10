TEMPLATE = app
TARGET = app

ROOT = ../../..
include($$ROOT/include/common.pri)

include(framelesshelper/framelesshelper.pri)
include(framework/framework.pri)
include(views/views.pri)

LIBS += xhpluginframework.lib xhcore.lib

CONFIG += qt c++11

QT += quick gui qml widgets winextras

RESOURCES += \
    Resource.qrc
	
RC_ICONS = logo.ico

PRECOMPILED_HEADER = stable.h
HEADERS += stable.h

SOURCES += \
    mian.cpp
