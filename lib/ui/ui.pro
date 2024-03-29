#-------------------------------------------------
#
# Project created by QtCreator 2019-08-02T21:42:03
#
#-------------------------------------------------

QT       += widgets

TARGET = ui
TEMPLATE = lib
CONFIG += staticlib c++17
CONFIG -= exceptions

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main-window.cpp

HEADERS += \
    main-window.h

FORMS += \
    main-window.ui

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../storage/release/ -lstorage
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../storage/debug/ -lstorage
else:unix: LIBS += -L$$OUT_PWD/../storage/ -lstorage

INCLUDEPATH += $$PWD/../storage
DEPENDPATH += $$PWD/../storage

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../storage/release/libstorage.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../storage/debug/libstorage.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../storage/release/storage.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../storage/debug/storage.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../storage/libstorage.a

