#-------------------------------------------------
#
# Project created by QtCreator 2016-10-22T22:05:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlayFair
TEMPLATE = app


SOURCES += main.cpp\
    palyfair.cpp \
    table.cpp \
    strdeal.cpp \
    hill.cpp \
    mainwindow.cpp

HEADERS  += mainwindow.h \
    table.h \
    playfair.h \
    strdeal.h \
    encrypt.h \
    hill.h \
    matrix.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

RC_FILE += \
	myico.rc
