#-------------------------------------------------
#
# Project created by QtCreator 2015-12-01T14:42:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HouseRentSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    person.cpp \
    house.cpp \
    contract.cpp

HEADERS  += mainwindow.h \
    person.h \
    house.h \
    contract.h

FORMS    += mainwindow.ui
