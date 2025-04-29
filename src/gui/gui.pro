TARGET = icp-fsm-app

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    gui/main.cpp \
    gui/mainwindow.cpp \
    parser/MooreMachine.cpp \
    parser/MooreState.cpp \
    parser/MooreStateFactory.cpp

HEADERS += \
    gui/mainwindow.h \
    parser/MooreMachine.h \
    parser/MooreState.h \
    parser/MooreStateFactory.h

FORMS += \
    gui/mainwindow.ui
