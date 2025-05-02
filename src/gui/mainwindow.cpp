// File: mainwindow.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FSMView.h"
#include "FSMScene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fsmView = ui->fsmGraphicsView;
    fsmScene = new FSMScene(this);
    fsmView->setScene(fsmScene);

    connect(fsmView, &FSMView::addStateRequested, fsmScene, &FSMScene::onAddState);
    connect(fsmView, &FSMView::addTransitionRequested, fsmScene, &FSMScene::onAddTransition);
}
MainWindow::~MainWindow()
{
    delete ui;
}
