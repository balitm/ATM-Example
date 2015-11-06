#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T12:28:29
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATM
TEMPLATE = app


SOURCES += main.cpp\
        atmdialog.cpp \
    cardmodel.cpp \
    networkmodel.cpp

HEADERS  += atmdialog.h \
    cardmodel.h \
    networkmodel.h

FORMS    += atmdialog.ui
