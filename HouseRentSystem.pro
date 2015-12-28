#-------------------------------------------------
#
# Project created by QtCreator 2015-12-01T14:42:01
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HouseRentSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    person.cpp \
    house.cpp \
    contract.cpp \
    configmanager.cpp \
    dialogeditperson.cpp \
    databasewrapper.cpp

HEADERS  += mainwindow.h \
    person.h \
    house.h \
    contract.h \
    configmanager.h \
    dialogeditperson.h \
    databasewrapper.h

FORMS    += mainwindow.ui \
    dialogeditperson.ui

DISTFILES += \
    sqlite3.lib
