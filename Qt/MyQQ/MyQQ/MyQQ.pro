#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T17:28:10
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyQQ
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mytoolbox.cpp \
    mylogin.cpp \
    myfuncset.cpp \
    myaddfriend.cpp \
    mywidget.cpp \
    mytoolboxcontainer.cpp \
    mysocket.cpp \
    myevent.cpp

HEADERS  += widget.h \
    mytoolbox.h \
    mylogin.h \
    myfuncset.h \
    myaddfriend.h \
    mywidget.h \
    mytoolboxcontainer.h \
    mysocket.h \
    myevent.h

RESOURCES += \
    headerImg.qrc
