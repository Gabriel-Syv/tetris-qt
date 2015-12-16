#-------------------------------------------------
#
# Project created by QtCreator 2015-12-13T12:54:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = Tetris
INCLUDEPATH += .

# Input
HEADERS += logic.h mainwindow.h piece.h
FORMS += mainwindow.ui
SOURCES += logic.cpp main.cpp mainwindow.cpp
