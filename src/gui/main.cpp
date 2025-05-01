// File: main.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QFile styleFile(":/darkstyle.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&styleFile);
        QString styleSheet = ts.readAll();
        w.setStyleSheet(styleSheet);
    }

    w.show();
    return a.exec();
}
