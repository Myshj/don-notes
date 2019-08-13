#-------------------------------------------------
#
# Project created by QtCreator 2019-08-06T21:40:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17
CONFIG -= exceptions

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/ui/release/ -lui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/ui/debug/ -lui
else:unix: LIBS += -L$$OUT_PWD/../lib/ui/ -lui

INCLUDEPATH += $$PWD/../lib/ui
DEPENDPATH += $$PWD/../lib/ui

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/ui/release/libui.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/ui/debug/libui.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/ui/release/ui.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/ui/debug/ui.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/ui/libui.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/storage/release/ -lstorage
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/storage/debug/ -lstorage
else:unix: LIBS += -L$$OUT_PWD/../lib/storage/ -lstorage

INCLUDEPATH += $$PWD/../lib/storage
DEPENDPATH += $$PWD/../lib/storage

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/storage/release/libstorage.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/storage/debug/libstorage.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/storage/release/storage.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/storage/debug/storage.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/storage/libstorage.a
