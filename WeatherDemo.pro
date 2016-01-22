#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T16:45:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeatherDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    weather.cpp

HEADERS  += mainwindow.h \
    weather.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

