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
