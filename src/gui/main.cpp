#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <vector>
#include "parser/AutomateJsonDocument.h"
#include "parser/MooreMachine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    MooreMachine mooreMachine;
    AutomateJsonDocument jsonDocument;
    jsonDocument.loadAutomateFromJsonFile("automate.json", mooreMachine);
    jsonDocument.saveAutomateToJsonFile("output.json", mooreMachine);
    std::cout
        << "Hello World" << std::endl;
    return a.exec();
}
