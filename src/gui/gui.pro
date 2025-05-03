TARGET = icp-fsm-app

QT += core \
      gui \
      qml 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 \ 
        moc

SOURCES += \
    FSMScene.cpp \
    FSMState.cpp \
    FSMTransition.cpp \
    FSMView.cpp \
    main.cpp \
    mainwindow.cpp \
    parser/MooreMachine.cpp \
    parser/MooreState.cpp \
    parser/MooreStateFactory.cpp \
    parser/AutomateJsonDocument.cpp \
    parser/ActionExecutor.cpp \
     parser/MooreMachineExecutor.cpp\
     parser/RunExecutionStrategy.cpp \
     parser/StepExecutionStrategy.cpp

HEADERS += \
    FSMScene.h \
    FSMState.h \
    FSMTransition.h \
    FSMView.h \
    mainwindow.h \
    parser/MooreMachine.h \
    parser/MooreState.h \
    parser/MooreStateFactory.h \
    parser/AutomateJsonDocument.h \
    parser/ActionExecutor.h \
    IExecutionStrategy.h \
    parser/MooreMachineExecutor.h\
     parser/RunExecutionStrategy.h \
     parser/StepExecutionStrategy.h

FORMS += \
    mainwindow.ui
