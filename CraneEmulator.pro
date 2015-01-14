#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T21:01:52
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CraneEmulator
TEMPLATE = app

INCLUDEPATH += view-top \
               view-side

include(view-top/Top.pri)
include(view-side/Side.pri)

SOURCES += main.cpp \
        widget.cpp \
        AbstractItem.cpp

HEADERS  += widget.h \
        AbstractItem.h

FORMS    += widget.ui

RESOURCES += \
    resources.qrc

OTHER_FILES +=
