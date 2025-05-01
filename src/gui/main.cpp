#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <vector>
#include "parser/AutomateJsonDocument.h"
#include "parser/MooreMachine.h"
#include "parser/ActionExecutor.h"
#include "parser/MooreAutomateSimulator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    MooreMachine mooreMachine;
    AutomateJsonDocument jsonDocument;
    jsonDocument.loadAutomateFromJsonFile("output.json", mooreMachine);
    MooreSimulator mooreSimulation(&mooreMachine);
    mooreSimulation.run();
    // jsonDocument.saveAutomateToJsonFile("output.json", mooreMachine);
    return a.exec();
}
