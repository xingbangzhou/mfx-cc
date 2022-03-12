isEmpty(ROOT) {
    error("ROOT must be defined.")
}
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/ffmpeg

QMAKE_CFLAGS += /WX /MP
QMAKE_CXXFLAGS += /WX /MP -Zc:__cplusplus -std:c++17
QMAKE_CFLAGS_RELEASE    = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_CXXFLAGS_RELEASE  = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
CharacterSet = 1

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17

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
