TARGET = icp-fsm-app

QT += core gui widgets qml

CONFIG += c++17 release

SOURCES += \
    FSMGui.cpp \
    FSMScene.cpp \
    FSMState.cpp \
    FSMTransition.cpp \
    FSMView.cpp \
    GenericRowWidget.cpp \
    TerminalWidget.cpp \
    TransitionRowWidget.cpp \
    main.cpp \
    mainwindow.cpp \
    ../parser/MooreMachine.cpp \
    ../parser/MooreState.cpp \
    ../parser/MooreStateFactory.cpp \
    ../parser/AutomateJsonDocument.cpp \
    ../parser/ActionExecutor.cpp \
    ../parser/MooreMachineExecutor.cpp\
    ../parser/RunExecutionStrategy.cpp \
    ../parser/StepExecutionStrategy.cpp \
    ForceDirectedLayout.cpp

HEADERS += \
    FSMGui.h \
    FSMScene.h \
    FSMState.h \
    FSMTransition.h \
    FSMView.h \
    TerminalWidget.h \
    TransitionRowWidget.h \
    mainwindow.h \
    ../parser/MooreMachine.h \
    ../parser/MooreState.h \
    ../parser/MooreStateFactory.h \
    ../parser/AutomateJsonDocument.h \
    ../parser/ActionExecutor.h \
    ../parser/IExecutionStrategy.h \
    ../parser/MooreMachineExecutor.h\
    ../parser/RunExecutionStrategy.h \
    ../parser/StepExecutionStrategy.h \
    GenericRowWidget.h \
    ForceDirectedLayout.h \
    ../parser/MooreJsClass.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resource.qrc
