// File: mainwindow.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FSMView.h"
#include "FSMScene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    FSMView *fsmView;
    FSMScene *fsmScene;
};
#endif // MAINWINDOW_H
