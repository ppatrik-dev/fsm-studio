// File: mainwindow.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FSMView.h"
#include "FSMScene.h"
#include "parser/AutomateJsonDocument.h"
#include "parser/MooreMachine.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fsmView = ui->fsmGraphicsView;
    fsmScene = new FSMScene(this);
    fsmView->setScene(fsmScene);

    machine = new MooreMachine();
    AutomateJsonDocument *jsonDocument = new AutomateJsonDocument(this);

    connect(this, &MainWindow::loadJsonRequested, jsonDocument, &AutomateJsonDocument::loadAutomateFromJsonFile);
    connect(this, &MainWindow::exportJsonRequested, jsonDocument, &AutomateJsonDocument::saveAutomateToJsonFile);
    connect(fsmView, &FSMView::addStateRequested, fsmScene, &FSMScene::onAddState);
    connect(fsmView, &FSMView::addTransitionRequested, fsmScene, &FSMScene::onAddTransition);

    emit loadJsonRequested("automate.json", *machine);
    emit exportJsonRequested("output1.json", *machine);
}
MainWindow::~MainWindow()
{
    delete ui;
}
