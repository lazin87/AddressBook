#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T15:17:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AddressBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addresswidget.cpp \
    tablemodel.cpp \
    newaddresstab.cpp \
    adddialog.cpp

HEADERS  += mainwindow.h \
    addresswidget.h \
    tablemodel.h \
    newaddresstab.h \
    adddialog.h

FORMS    += mainwindow.ui
