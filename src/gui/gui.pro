TARGET = icp-fsm-app

QT += core \
      gui \
      qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    gui/main.cpp \
    gui/mainwindow.cpp \
    parser/MooreMachine.cpp \
    parser/MooreState.cpp \
    parser/MooreStateFactory.cpp \
    parser/AutomateJsonDocument.cpp \
    parser/ActionExecutor.cpp \
     parser/MooreAutomateSimulator.cpp

HEADERS += \
    gui/mainwindow.h \
    parser/MooreMachine.h \
    parser/MooreState.h \
    parser/MooreStateFactory.h \
    parser/AutomateJsonDocument.h \
    parser/ActionExecutor.h \
    parser/MooreAutomateSimulator.h

FORMS += \
    gui/mainwindow.ui
