// File: mainwindow.cpp
// Author: Patrik Prochazka, Filip Ficka
// Login: xprochp00, xfickaf00

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FSMView.h"
#include "FSMScene.h"
#include "../parser/AutomateJsonDocument.h"
#include "../parser/MooreMachine.h"
#include "TransitionRowWidget.h"
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
    fsmGui = new FSMGui(fsmScene);

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
    connect(fsmGui, &FSMGui::inputAddValue, machine, &MooreMachine::addGuiInput);
    connect(fsmGui, &FSMGui::inputDeleteValue, machine, &MooreMachine::deleteGuiInput);
    connect(fsmGui, &FSMGui::outputAddValue, machine, &MooreMachine::addGuiOutput);
    connect(fsmGui, &FSMGui::outputDeleteValue, machine, &MooreMachine::deleteGuiOutput);
    connect(fsmGui, &FSMGui::variableAddValue, machine, &MooreMachine::addGuiVariable);
    connect(fsmGui, &FSMGui::variableDeleteValue, machine, &MooreMachine::deleteGuiVariable);

    connect(fsmGui, &FSMGui::saveNameValue, machine, &MooreMachine::setName);
    connect(fsmGui, &FSMGui::saveDescriptionValue, machine, &MooreMachine::setComment);

    // FSM scale
    connect(ui->fsmGraphicsView, &FSMView::zoomChanged, this, [=](int percent)
            { ui->zoomLabel->setText(QString::number(percent) + "%"); });

    connect(fsmScene, &FSMScene::initialStateDeleted, fsmGui, &FSMGui::setInitialState);

    // FSM editing
    connect(fsmView, &FSMView::addStateRequested, fsmScene, &FSMScene::onAddState);
    connect(fsmView, &FSMView::addTransitionRequested, fsmScene, &FSMScene::onAddTransition);
    connect(fsmView, &FSMView::deleteStateRequested, fsmScene, &FSMScene::onDeleteState);
    connect(fsmView, &FSMView::deleteTransitionRequested, fsmScene, &FSMScene::onDeleteTransition);

    // Details panel
    connect(fsmScene, &FSMScene::itemSelected, this, &MainWindow::showDetailsPanel);

    // Initial state changed
    // connect(fsmGui, &FSMGui::initialStateChanged, ) TODO: Connect signal to Mirek slot

    // Init layouts
    inputsLayout = new QVBoxLayout();
    outputsLayout = new QVBoxLayout();
    variablesLayout = new QVBoxLayout();

    ui->scrollInWidgets->setLayout(inputsLayout);
    ui->scrollOutWidgets->setLayout(outputsLayout);
    ui->scrollVarWidgets->setLayout(variablesLayout);

    // map buttons to add row func
    connect(ui->addInputButton, &QPushButton::clicked, this, &MainWindow::onAddInputClicked);
    connect(ui->addOutputButton, &QPushButton::clicked, this, &MainWindow::onAddOutputClicked);
    connect(ui->addVariableButton, &QPushButton::clicked, this, &MainWindow::onAddVariableClicked);

    // Add condition
    connect(ui->addConditionButton, &QPushButton::clicked, this, &MainWindow::onAddConditionClicked);

    // FSM name
    connect(ui->automataNameLineEdit, &QLineEdit::editingFinished, this, [=]()
            { fsmGui->saveName(ui->automataNameLineEdit->text()); });

    // FSM description
    connect(ui->automataDescriptionTextEdit, &QTextEdit::textChanged, this, [=]()
            { fsmGui->saveDescription(ui->automataDescriptionTextEdit->toPlainText());} );

    // Inputs
    connect(ui->saveInputsButton, &QPushButton::clicked, this, [=]()
            { fsmGui->saveInputs(inputsWidgets); });
    // Outputs
    connect(ui->saveOutputsbutton, &QPushButton::clicked, this, [=]()
            { fsmGui->saveOutputs(outputsWidgets); });
    // Variables
    connect(ui->saveVariablesButton, &QPushButton::clicked, this, [=]()
            { fsmGui->saveVariables(variablesWidgets); });
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

    /*
     * fsmGui->displayName(QString name);
     * fsmGui->displayDescription(QString description);
     * fsmGui()->displayInputs(list(string, string);
     */
}

// MENU
void MainWindow::showDetailsPanel(QGraphicsItem *item)
{
    if (!item || item->type() != FSMState::Type)
    {
        ui->detailsPanel->setCurrentWidget(ui->automataPropertiesPanel);
        return;
    }

    clearConditionRows();
    ui->detailsPanel->setCurrentWidget(ui->statePropertiesPanel);

    FSMState *state = qgraphicsitem_cast<FSMState*>(item);

    // State name
    ui->stateNameLineEdit->setText(state->getLabel());
    ui->stateNameLineEdit->setReadOnly(true);

    disconnect(ui->initialStatePushButton, nullptr, nullptr, nullptr);
    connect(ui->initialStatePushButton, &QPushButton::clicked, this, [this, state]() {
        fsmGui->setInitialState(state);
    });

    // Display conditions
    for (auto condition : state->getConditions()){
        auto row = onAddConditionClicked();
        row->setTransitionTexts(condition.first, condition.second);
    }

    // Add new condition to new transition
    disconnect(fsmScene, &FSMScene::addNewTransition, nullptr, nullptr);
    connect(fsmScene, &FSMScene::addNewTransition, this, [=](FSMTransition *transition) {
        auto row = onAddConditionClicked();
        auto edit = row->getToStateEdit();
        edit->setText(transition->getSecondState()->getLabel());;
        edit->setReadOnly(true);
        transition->setRow(row);
    });

    // Save conditions
    disconnect(ui->saveConditionsButton, nullptr, nullptr, nullptr);
    connect(ui->saveConditionsButton, &QPushButton::clicked, this, [state, this]() {
        state->saveConditions(conditionWidgets);
    });
}

// CONDITIONS
TransitionRowWidget* MainWindow::onAddConditionClicked()
{
    auto *row = new TransitionRowWidget();

    ui->conditionsLayout->addWidget(row);

    connect(row, &TransitionRowWidget::requestDelete, this, &MainWindow::onDeleteCondition);

    conditionWidgets.append(row);

    return row;
}

void MainWindow::onDeleteCondition(TransitionRowWidget *row)
{
    ui->conditionsLayout->removeWidget(row);
    conditionWidgets.removeAll(row);
    row->deleteLater();
}

// INPUTS
void MainWindow::onAddInputClicked()
{
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Input);

    inputsLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, &MainWindow::onDeleteRow);

    inputsWidgets.append(row);
}

// OUTPUTS
void MainWindow::onAddOutputClicked()
{
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Output, this);
    outputsLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, &MainWindow::onDeleteRow);

    outputsWidgets.append(row);
}

// VARIABLES
void MainWindow::onAddVariableClicked()
{
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Variable, this);
    variablesLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, &MainWindow::onDeleteRow);

    variablesWidgets.append(row);
}

void MainWindow::onDeleteRow(GenericRowWidget *row)
{
    if (!row)
        return;

    // from which layout it came
    if (inputsLayout->indexOf(row) != -1)
    {
        inputsLayout->removeWidget(row);
        inputsWidgets.removeAll(row);
        fsmGui->deleteInput(row->key());
    }
    else if (outputsLayout->indexOf(row) != -1)
    {
        outputsLayout->removeWidget(row);
        outputsWidgets.removeAll(row);
        fsmGui->deleteOutput(row->key());
    }
    else if (variablesLayout->indexOf(row) != -1)
    {
        variablesLayout->removeWidget(row);
        variablesWidgets.removeAll(row);
        fsmGui->deleteVariable(row->key());
    }

    row->deleteLater();
}

void MainWindow::clearConditionRows()
{
    for (auto row : conditionWidgets)
    {
        if (row)
            row->deleteLater();
    }
    conditionWidgets.clear();
}
