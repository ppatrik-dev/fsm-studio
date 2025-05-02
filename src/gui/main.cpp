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
    // w.show();
    MooreMachine mooreMachine;
    AutomateJsonDocument jsonDocument;
    jsonDocument.loadAutomateFromJsonFile("automate.json", mooreMachine);

    MachineExecutor executor(&mooreMachine);

    RunExecutionStrategy runStrategy;
    StepExecutionStrategy stepStrategy;

    executor.SetStrategy(&runStrategy);
    executor.Execute(mooreMachine);

    jsonDocument.saveAutomateToJsonFile("output.json", mooreMachine);
    return a.exec();
}
