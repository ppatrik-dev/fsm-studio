/**
 * @file main.cpp
 * @author Patrik Prochazka (xprochp00@vutbr.cz)
 * @brief Source file 
 * @version 0.1
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "mainwindow.h"
#include <QApplication>
#include <QTextStream>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    window.setWindowTitle("FSM Studio");
    // window.setWindowIcon(QIcon(":/icons/app-icon"));

    QFile styleFile(":/darkstyle.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream ts(&styleFile);
        QString styleSheet = ts.readAll();
        window.setStyleSheet(styleSheet);
    }

    window.show();
    return app.exec();
}
