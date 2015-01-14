#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T21:01:52
#
#-------------------------------------------------

QT       += core gui svg xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CraneEmulator
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    AbstractItem.cpp \
    RopeHookItem.cpp \
    TelescopicItem.cpp \
    DerrickItem.cpp \
    OutriggerItem.cpp \
    HookItem.cpp \
    PillarItem.cpp \
    OtherItem.cpp \
    EllipseOutriggerItem.cpp \
    EllipseHookItem.cpp \
    CrutchItem.cpp

HEADERS  += widget.h \
    AbstractItem.h \
    RopeHookItem.h \
    TelescopicItem.h \
    DerrickItem.h \
    OutriggerItem.h \
    HookItem.h \
    PillarItem.h \
    OtherItem.h \
    EllipseOutriggerItem.h \
    EllipseHookItem.h \
    CrutchItem.h

FORMS    += widget.ui

RESOURCES += \
    resources.qrc
