// File: main.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "mainwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <vector>
#include "parser/AutomateJsonDocument.h"
#include "parser/MooreMachine.h"
#include "parser/ActionExecutor.h"
#include "parser/MooreMachineExecutor.h"
#include "parser/RunExecutionStrategy.h"
#include "parser/StepExecutionStrategy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;

    // QFile styleFile(":/darkstyle.qss");
    // if (styleFile.open(QFile::ReadOnly | QFile::Text))
    // {
    //     QTextStream ts(&styleFile);
    //     QString styleSheet = ts.readAll();
    //     w.setStyleSheet(styleSheet);
    // }

    // w.show();
    // MainWindow w;
    // w.show();
    MooreMachine mooreMachine;
    AutomateJsonDocument jsonDocument;
    jsonDocument.loadAutomateFromJsonFile("automate.json", mooreMachine);

    MachineExecutor executor(&mooreMachine);

    RunExecutionStrategy runStrategy;
    StepExecutionStrategy stepStrategy;

    executor.SetStrategy(&runStrategy);
    executor.Execute(mooreMachine);

    return a.exec();
}
