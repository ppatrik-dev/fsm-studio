TARGET = icp-fsm-app

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer
QMAKE_LFLAGS += -fsanitize=address

CONFIG += c++17 \
        debug

SOURCES += \
    ConditionRowWidget.cpp \
    FSMScene.cpp \
    FSMState.cpp \
    FSMTransition.cpp \
    FSMView.cpp \
    GenericRowWidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ConditionRowWidget.h \
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
