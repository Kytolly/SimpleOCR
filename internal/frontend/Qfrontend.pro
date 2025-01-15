QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release){
    DESTDIR = $$PWD/bin/debug
}else{
    DESTDIR = $$PWD/bin/release
}

INCLUDEPATH += D:\SDK\libzmp\4.3.5\msvc2019\include

win32{
CONFIG(debug, debug|release){
LIBS +=D:\SDK\libzmp\4.3.5\msvc2019\lib\Debug\libzmq-v142-mt-gd-4_3_5.lib
}
else{
 LIBS +=D:\SDK\libzmp\4.3.5\msvc2019\lib\release\libzmq-v142-mt-4_3_5.lib
}
}

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    net_api.cpp \
    worker.cpp

HEADERS += \
    QImageLabel.h \
    mainwindow.h \
    nlohmann/json.hpp \
    nlohmann/json_fwd.hpp \
    worker.h \
    zmq.hpp \
    zmq_addon.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
    frontend_zh_CN.ts
