#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T19:00:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = Pilkarzyki
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pitch.cpp \
    team.cpp \
    moveableitem.cpp \
    player.cpp \
    ball.cpp \
    physicsengine.cpp

HEADERS  += mainwindow.h \
    pitch.h \
    team.h \
    moveableitem.h \
    player.h \
    ball.h \
    physicsengine.h

FORMS    += mainwindow.ui
