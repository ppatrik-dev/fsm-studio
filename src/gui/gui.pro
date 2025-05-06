TARGET = icp-fsm-app

QT += core \
      gui \
      qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer
QMAKE_LFLAGS += -fsanitize=address

CONFIG += c++17 \
        debug

SOURCES += \
    ConditionRowWidget.cpp \
    FSMGui.cpp \
    FSMScene.cpp \
    FSMState.cpp \
    FSMTransition.cpp \
    FSMView.cpp \
    GenericRowWidget.cpp \
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
    ConditionRowWidget.h \
    FSMGui.h \
    FSMScene.h \
    FSMState.h \
    FSMTransition.h \
    FSMView.h \
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
