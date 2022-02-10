QT += winextras

INCLUDEPATH += $$PWD
LIBS += -lUser32

HEADERS += \
    $$PWD/framelesshelper.h \
    $$PWD/framelesshelper_p.h \
    $$PWD/windowframelesshelper.h \
    $$PWD/windowframelesshelper_p.h
SOURCES += \
    $$PWD/framelesshelper.cpp \
    $$PWD/windowframelesshelper.cpp

HEADERS += \
    $$PWD/kernels/nativewindowfilter.h \
    $$PWD/kernels/nativewindowfilter_p.h \
    $$PWD/kernels/nativewindowhelper.h \
    $$PWD/kernels/nativewindowhelper_p.h
SOURCES += \
    $$PWD/kernels/nativewindowfilter.cpp \
    $$PWD/kernels/nativewindowhelper.cpp
