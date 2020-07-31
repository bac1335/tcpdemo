
QT += network

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/llstcpdef.h \
    $$PWD/llstcptransbase.h \
    $$PWD/llstcptransserver.h

SOURCES += \
    $$PWD/llstcptransbase.cpp \
    $$PWD/llstcptransserver.cpp
