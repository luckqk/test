#-------------------------------------------------
#
# Project created by QtCreator 2019-05-02T21:49:41
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = picResearch
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

CONFIG += c++11

UI_DIR=./UI

SOURCES += \
        main.cpp \
        picremainwindow.cpp \
    qformdoc.cpp \
    qformtcp.cpp \
    qformtcpserver.cpp

HEADERS += \
        picremainwindow.h \
    qformdoc.h \
    ../build-picResearch-Desktop_Qt_5_9_1_MSVC2017_64bit-Debug/ui_picremainwindow.h \
    ../build-picResearch-Desktop_Qt_5_9_1_MSVC2017_64bit-Debug/ui_qformdoc.h \
    ../build-picResearch-Desktop_Qt_5_9_1_MSVC2017_64bit-Debug/ui_qformtcp.h \
    qformdoc.h \
    qformtcp.h \
    qformtcpserver.h

FORMS += \
        picremainwindow.ui \
    picremainwindow.ui \
    qformdoc.ui \
    qformtcp.ui \
    qformtcpserver.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
