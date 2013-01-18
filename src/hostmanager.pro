#-------------------------------------------------
#
# Project created by QtCreator 2011-03-28T20:12:54
#
#-------------------------------------------------

QT       += core gui
CONFIG += static
TARGET = hostmanager
TEMPLATE = app


SOURCES += main.cpp \
    hostmanagerapplication.cpp \
    addhostwindow.cpp \
    hostfilemanager.cpp \
    hostrecord.cpp \
    hostmenu.cpp \
    edithostwindow.cpp \
    aboutdialog.cpp

HEADERS  += \
    hostmanagerapplication.hpp \
    addhostwindow.hpp \
    hostfilemanager.hpp \
    hostrecord.hpp \
    hostmenu.hpp \
    edithostwindow.hpp \
    aboutdialog.hpp

RESOURCES += \
    gfx.qrc

FORMS += \
    addhostwindow.ui \
    edithostwindow.ui \
    aboutdialog.ui

RC_FILE = hostmanager.rc
