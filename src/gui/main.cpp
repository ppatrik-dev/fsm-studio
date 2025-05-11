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
#include "../parser/AutomateJsonDocument.h"
#include "../parser/MooreMachine.h"
#include "../parser/ActionExecutor.h"
#include "../parser/MooreMachineExecutor.h"
#include "../parser/RunExecutionStrategy.h"
#include "../parser/StepExecutionStrategy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    a.setWindowIcon(QIcon(":/icons/app-icon.png"));
    w.setWindowIcon(QIcon(":/icons/app-icon.png"));

    QFile styleFile(":/darkstyle.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream ts(&styleFile);
        QString styleSheet = ts.readAll();
        w.setStyleSheet(styleSheet);
    }

    w.show();
    return a.exec();
}
