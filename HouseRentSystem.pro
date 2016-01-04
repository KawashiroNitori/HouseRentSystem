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
    dialogeditperson.cpp \
    dialogselectperson.cpp \
    databasemanager.cpp \
    dialogedithouse.cpp \
    dialogselecthouse.cpp \
    dialogeditcontract.cpp

HEADERS  += mainwindow.h \
    person.h \
    house.h \
    contract.h \
    dialogeditperson.h \
    dialogselectperson.h \
    databasemanager.h \
    dialogedithouse.h \
    dialogselecthouse.h \
    dialogeditcontract.h

FORMS    += mainwindow.ui \
    dialogeditperson.ui \
    dialogselectperson.ui \
    dialogedithouse.ui \
    dialogselecthouse.ui \
    dialogeditcontract.ui

DISTFILES +=
