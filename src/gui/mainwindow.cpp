// File: mainwindow.cpp
// Author: Patrik Prochazka, Filip Ficka
// Login: xprochp00, xfickaf00

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FSMView.h"
#include "FSMScene.h"
#include "parser/AutomateJsonDocument.h"
#include "parser/MooreMachine.h"
#include "ConditionRowWidget.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fsmView = ui->fsmGraphicsView;
    fsmScene = new FSMScene(this);
    fsmView->setScene(fsmScene);

    // connect(ui->zoomInButton, &QPushButton::clicked, ui->fsmGraphicsView, &FSMView::zoomIn);
    // connect(ui->zoomOutButton, &QPushButton::clicked, ui->fsmGraphicsView, &FSMView::zoomOut);
    connect(ui->fsmGraphicsView, &FSMView::zoomChanged, this, [=](int percent)
            { ui->zoomLabel->setText(QString::number(percent) + "%"); });

    machine = new MooreMachine();
    AutomateJsonDocument *jsonDocument = new AutomateJsonDocument(this);

    connect(this, &MainWindow::loadJsonRequested, jsonDocument, &AutomateJsonDocument::loadAutomateFromJsonFile);
    connect(this, &MainWindow::exportJsonRequested, jsonDocument, &AutomateJsonDocument::saveAutomateToJsonFile);
    connect(this, &MainWindow::createMachine, fsmScene, &FSMScene::createMachineFile);
    // Control buttons
    connect(ui->clearButton, &QPushButton::clicked, fsmScene, &FSMScene::onClearScene);
    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::onImportFileClicked);
    // FSM scale
    connect(ui->fsmGraphicsView, &FSMView::zoomChanged, this, [=](int percent)
            { ui->zoomLabel->setText(QString::number(percent) + "%"); });

    // FSM editing
    connect(fsmView, &FSMView::addStateRequested, fsmScene, &FSMScene::onAddState);
    connect(fsmView, &FSMView::addTransitionRequested, fsmScene, &FSMScene::onAddTransition);
    connect(fsmView, &FSMView::deleteStateRequested, fsmScene, &FSMScene::onDeleteState);
    connect(fsmView, &FSMView::deleteTransitionRequested, fsmScene, &FSMScene::onDeleteTransition);

    // Details panel
    connect(fsmScene, &FSMScene::itemSelected, this, [=](QGraphicsItem *item)
            {
        if (!item) {
            ui->rightPanel->setCurrentWidget(ui->automataPropertiesPanel);
        }
        else if (item->type() == FSMState::Type)
        {
            ui->rightPanel->setCurrentWidget(ui->statePropertiesPanel);
        }
        else {
            ui->rightPanel->setCurrentWidget(ui->automataPropertiesPanel);
        } });

    // Init layouts
    inputsLayout = new QVBoxLayout();
    outputsLayout = new QVBoxLayout();
    variablesLayout = new QVBoxLayout();

    ui->scrollInWidgets->setLayout(inputsLayout);
    ui->scrollOutWidgets->setLayout(outputsLayout);
    ui->scrollVarWidgets->setLayout(variablesLayout);

    // map buttons to addrow func
    connect(ui->addInput, &QPushButton::clicked, this, &MainWindow::onAddRowButtonClicked);
    connect(ui->addOutput, &QPushButton::clicked, this, &MainWindow::onAddOutputClicked);
    connect(ui->addVariable, &QPushButton::clicked, this, &MainWindow::onAddVariableClicked);

    connect(ui->addConditionButton, &QPushButton::clicked, this, [=]()
            {
        auto *row = new ConditionRowWidget();
        ui->conditionsLayout->addWidget(row);

        connect(row, &ConditionRowWidget::requestDelete, this, [=]()
                {
            ui->conditionsLayout->removeWidget(row);
            row->deleteLater(); }); });

    // emit loadJsonRequested("automate.json", *machine);
    // emit createMachine(*machine);
    // emit exportJsonRequested("output1.json", *machine);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onImportFileClicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), "JSON FIle (*.json*)");
    emit loadJsonRequested(filename, *machine);
    emit createMachine(*machine);
}

// INPUTS
void MainWindow::onAddRowButtonClicked()
{
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Input);
    inputsLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, [=]()
            {
        inputsLayout->removeWidget(row);
        row->deleteLater(); });
}

// OUTPUTS
void MainWindow::onAddOutputClicked()
{
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Output);
    outputsLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, [=]()
            {
        outputsLayout->removeWidget(row);
        row->deleteLater(); });
}

// VARIABLES
void MainWindow::onAddVariableClicked()
{
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Variable);
    variablesLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, [=]()
            {
        variablesLayout->removeWidget(row);
        row->deleteLater(); });
}

void MainWindow::onDeleteRow(GenericRowWidget *row)
{
    if (!row)
        return;

    // from which layout it came
    if (inputsLayout->indexOf(row) != -1)
    {
        inputsLayout->removeWidget(row);
    }
    else if (outputsLayout->indexOf(row) != -1)
    {
        outputsLayout->removeWidget(row);
    }
    else if (variablesLayout->indexOf(row) != -1)
    {
        variablesLayout->removeWidget(row);
    }

    row->deleteLater();
}
