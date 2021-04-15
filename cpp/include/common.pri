isEmpty(ROOT) {
    error("ROOT must be defined.")
}

INCLUDEPATH += $$PWD
QMAKE_CFLAGS += /WX /MP
QMAKE_CXXFLAGS += /WX /MP
QMAKE_CFLAGS_RELEASE    = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_CXXFLAGS_RELEASE  = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_CXXFLAGS_RTTI_OFF = -GR-
CONFIG += rtti_off
CONFIG -= embed_manifest_dll
CharacterSet = 1

CONFIG(debug, debug|release) {
    QMAKE_LIBDIR += $$ROOT/bin/debug
    DESTDIR = $$ROOT/bin/debug
}
else {
    QMAKE_LIBDIR += $$ROOT/bin/release
    DESTDIR = $$ROOT/bin/release
}

!static:equals(TEMPLATE, "lib") {
    QMAKE_LFLAGS += /MANIFEST:NO
}

DEFINES += NOMINMAX
QMAKE_LFLAGS_RELEASE += /DEBUG
