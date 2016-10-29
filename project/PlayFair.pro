#-------------------------------------------------
#
# Project created by QtCreator 2016-10-22T22:05:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlayFair
TEMPLATE = app


SOURCES +=  \
    ../src/hill.cpp \
    ../src/main.cpp \
    ../src/mainwindow.cpp \
    ../src/palyfair.cpp \
    ../src/strdeal.cpp \
    ../src/table.cpp

HEADERS  +=  \
    ../include/encrypt.h \
    ../include/hill.h \
    ../include/mainwindow.h \
    ../include/matrix.h \
    ../include/playfair.h \
    ../include/strdeal.h \
    ../include/table.h

FORMS    += mainwindow.ui

RESOURCES += \
	res.qrc

