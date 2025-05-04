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
#include "FSMState.h"
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
    machine = new MooreMachine(this);
    fsmScene->setMachine(machine);
    fsmScene->addConnects();

    // connect(ui->zoomInButton, &QPushButton::clicked, ui->fsmGraphicsView, &FSMView::zoomIn);
    // connect(ui->zoomOutButton, &QPushButton::clicked, ui->fsmGraphicsView, &FSMView::zoomOut);
    connect(ui->fsmGraphicsView, &FSMView::zoomChanged, this, [=](int percent)
            { ui->zoomLabel->setText(QString::number(percent) + "%"); });

    AutomateJsonDocument *jsonDocument = new AutomateJsonDocument(this);

    connect(this, &MainWindow::loadJsonRequested, jsonDocument, &AutomateJsonDocument::loadAutomateFromJsonFile);
    connect(this, &MainWindow::exportJsonRequested, jsonDocument, &AutomateJsonDocument::saveAutomateToJsonFile);
    connect(this, &MainWindow::createMachine, fsmScene, &FSMScene::createMachineFile);
    // Control buttons
    connect(ui->clearButton, &QPushButton::clicked, fsmScene, &FSMScene::onClearScene);
    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::onImportFileClicked);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::onExportFileClicked);
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
            clearConditionWidgets();
        }

        else if (item->type() == FSMState::Type) {            
            ui->rightPanel->setCurrentWidget(ui->statePropertiesPanel);

            FSMState *state = qgraphicsitem_cast<FSMState*>(item);
            ui->stateNameLineEdit->setText(state->getLabel());

            // Display conditions
            for (auto condition : state->getConditions()) {
                auto row = new ConditionRowWidget();
                row->setConditionTexts(condition.first, condition.second);

                conditionWidgets.append(row);
                ui->conditionsLayout->addWidget(row);

                connect(row, &ConditionRowWidget::requestDelete, this, [=]() {
                    ui->conditionsLayout->removeWidget(row);
                    conditionWidgets.removeAll(row);
                    row->deleteLater();
                });
            }

            // Save conditions
            disconnect(ui->saveConditionsButton, nullptr, nullptr, nullptr);
            connect(ui->saveConditionsButton, &QPushButton::clicked, this, [state, this]() {
                state->saveConditions(conditionWidgets);
            });
        }
        else {
            ui->rightPanel->setCurrentWidget(ui->automataPropertiesPanel);
            clearConditionWidgets();
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
        auto *row = new ConditionRowWidget(this);
        ui->conditionsLayout->addWidget(row);

        connect(row, &ConditionRowWidget::requestDelete, this, [=]()
                {
            ui->conditionsLayout->removeWidget(row);
            conditionWidgets.removeAll(row);
            row->deleteLater();
        });

        conditionWidgets.append(row); });

    // auto *test = new ConditionRowWidget();
    // ui->conditionsLayout->addWidget(test);

    // connect(test, &ConditionRowWidget::requestDelete, this, [=]() {
    //     ui->conditionsLayout->removeWidget(test);
    //     test->deleteLater();
    // });

    // test->setConditionTexts("x > 5", "doSomething()");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onExportFileClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "JSON FIle (*.json*)");

    if (!fileName.isEmpty())
    {
        emit exportJsonRequested(fileName, *machine);
    }
    else
    {
        qDebug() << "File saving was canceled.";
    }
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
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Input, this);
    inputsLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, [=]()
            {
        inputsLayout->removeWidget(row);
        row->deleteLater(); });
}

// OUTPUTS
void MainWindow::onAddOutputClicked()
{
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Output, this);
    outputsLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, [=]()
            {
        outputsLayout->removeWidget(row);
        row->deleteLater(); });
}

// VARIABLES
void MainWindow::onAddVariableClicked()
{
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Variable, this);
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
void MainWindow::clearConditionWidgets()
{
    for (ConditionRowWidget *row : conditionWidgets)
    {
        if (row)
        {
            row->deleteLater();
        }
    }
    conditionWidgets.clear();
}
