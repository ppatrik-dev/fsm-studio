TARGET = icp-fsm-app

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    FSMScene.cpp \
    FSMState.cpp \
    FSMTransition.cpp \
    FSMView.cpp \
    GenericRowWidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    FSMScene.h \
    FSMState.h \
    FSMTransition.h \
    FSMView.h \
    GenericRowWidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
