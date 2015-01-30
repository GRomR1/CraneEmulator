QT       += core gui svg multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CraneEmulator
TEMPLATE = app

INCLUDEPATH += view-top \
               view-side \
               qextserialport-1.2rc
include(view-top/Top.pri)
include(view-side/Side.pri)
include(qextserialport-1.2rc/qextserialport.pri)


SOURCES += main.cpp \
        AbstractItem.cpp \
    PortSelector.cpp \
    PortListener.cpp \
    MainWindow.cpp \
    CraneWidget.cpp

HEADERS  += \
        AbstractItem.h \
    PortSelector.h \
    PortListener.h \
    MainWindow.h \
    ../Defines.h \
    CraneWidget.h

FORMS    += \
    PortSelector.ui \
    MainWindow.ui \
    CraneWidget.ui

RESOURCES += \
    resources.qrc

win32:RC_FILE += file.rc

QMAKE_LFLAGS += -static -static-libgcc
