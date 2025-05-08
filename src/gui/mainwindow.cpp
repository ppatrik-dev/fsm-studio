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

    FSMState::m_layout = ui->conditionsLayout;

    connect(ui->fsmGraphicsView, &FSMView::zoomChanged, this, [=](int percent)
            { ui->zoomLabel->setText(QString::number(percent) + "%"); });

    AutomateJsonDocument *jsonDocument = new AutomateJsonDocument(this);

    connect(this, &MainWindow::loadJsonRequested, jsonDocument, &AutomateJsonDocument::loadAutomateFromJsonFile);
    connect(this, &MainWindow::exportJsonRequested, jsonDocument, &AutomateJsonDocument::saveAutomateToJsonFile);
    connect(this, &MainWindow::createMachine, fsmScene, &FSMScene::createMachineFile);
    connect(this, &MainWindow::clearMachine, machine, &MooreMachine::clearMachine);
    connect(this, &MainWindow::importDetailsRequested, fsmGui, &FSMGui::importDetails);
    connect(fsmGui, &FSMGui::displayDetailsRequested, this, &MainWindow::displayFSMDetais);

    // Control buttons
    connect(ui->clearButton, &QPushButton::clicked, this, [=](){
        fsmScene->clearScene();   emit clearMachine();
    });
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

    connect(fsmGui, &FSMGui::getVarValue, machine, &MooreMachine::getGuiMap);
    connect(fsmGui, &FSMGui::getNameValue, machine, &MooreMachine::getGuiName);
    connect(fsmGui, &FSMGui::getDescriptionValue, machine, &MooreMachine::getGuiComment);
    connect(fsmGui, &FSMGui::getStartStateValue, machine, &MooreMachine::getGuiStartState);

    // Control buttons

    // FSM scale
    connect(ui->fsmGraphicsView, &FSMView::zoomChanged, this, [=](int percent)
            { ui->zoomLabel->setText(QString::number(percent) + "%"); });

    connect(fsmScene, &FSMScene::initialStateDeleted, fsmGui, &FSMGui::setInitialState);
    connect(fsmScene, &FSMScene::deleteStateRequested, machine, &MooreMachine::deleteState);
    connect(fsmScene, &FSMScene::deleteTransitionRequested, machine, &MooreMachine::deleteTransition);

    // FSM editing
    connect(fsmView, &FSMView::addStateRequested, fsmScene, &FSMScene::onAddState);
    connect(fsmView, &FSMView::addTransitionRequested, fsmScene, &FSMScene::onAddTransition);
    connect(fsmView, &FSMView::deleteStateRequested, fsmScene, &FSMScene::onDeleteState);
    // connect(fsmView, &FSMView::deleteTransitionRequested, fsmScene, &FSMScene::onDeleteTransition);

    // Details panel
    connect(fsmScene, &FSMScene::itemSelected, this, &MainWindow::showDetailsPanel);

    // Initial state changed
    connect(fsmGui, &FSMGui::initialStateChanged, machine, &MooreMachine::setStartState);

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
    connect(ui->addConditionButton, &QPushButton::clicked, this, &MainWindow::onAddTransitionClicked);

    // FSM name
    connect(ui->automataNameLineEdit, &QLineEdit::editingFinished, this, [=]()
            { fsmGui->saveName(ui->automataNameLineEdit->text()); });

    // FSM description
    connect(ui->automataDescriptionTextEdit, &QTextEdit::textChanged, this, [=]()
            { fsmGui->saveDescription(ui->automataDescriptionTextEdit->toPlainText()); });

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
    emit clearMachine();
    emit loadJsonRequested(filename, *machine);
    emit createMachine(*machine);
    emit importDetailsRequested();
}

GenericRowWidget* MainWindow::createDetailsRow(QVBoxLayout *layout, QList<GenericRowWidget*> &widgets, GenericRowWidget::RowType type)
{
    GenericRowWidget *row = new GenericRowWidget(type, this);
    layout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, &MainWindow::onDeleteRow);

    widgets.append(row);

    return row;
}

void MainWindow::displayFSMDetais() {
    ui->automataNameLineEdit->setText(fsmGui->getName());
    ui->automataDescriptionTextEdit->setText(fsmGui->getDescription());

    for (const QString key : fsmGui->getInputs().keys()) {
        GenericRowWidget *row = createDetailsRow(inputsLayout, inputsWidgets, GenericRowWidget::Input);
        qDebug() << fsmGui->getInputs().value(key);
        row->setGenericTexts(key, fsmGui->getInputs().value(key));
    }

    for (const QString key : fsmGui->getOutputs().keys()) {
        GenericRowWidget *row = createDetailsRow(outputsLayout, outputsWidgets, GenericRowWidget::Output);
        row->setGenericTexts(key, fsmGui->getOutputs().value(key));
    }

    for (const QString key : fsmGui->getVariables().keys()) {
        GenericRowWidget *row = createDetailsRow(variablesLayout, variablesWidgets, GenericRowWidget::Variable);
        row->setGenericTexts(key, fsmGui->getVariables().value(key));
    }
}

// MENU
void MainWindow::showDetailsPanel(QGraphicsItem *item)
{
    if (!item || item->type() != FSMState::Type)
    {
        ui->detailsPanel->setCurrentWidget(ui->automataPropertiesPanel);
        selectedState = nullptr;
        return;
    }

    detachWidgetsFromLayout(ui->conditionsLayout);
    ui->detailsPanel->setCurrentWidget(ui->statePropertiesPanel);

    FSMState *state = qgraphicsitem_cast<FSMState *>(item);
    selectedState = state;

    // State name
    ui->stateNameLineEdit->setText(state->getLabel());
    ui->stateNameLineEdit->setReadOnly(true);

    // Initial state
    disconnect(ui->initialStatePushButton, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->initialStatePushButton, &QPushButton::clicked, this, [this, state]()
            { fsmGui->setInitialState(state); });

    // State output
    ui->stateOutputLineEdit->setText(state->getOutput());

    disconnect(ui->stateOutputLineEdit, &QLineEdit::editingFinished, nullptr, nullptr);
    connect(ui->stateOutputLineEdit, &QLineEdit::editingFinished, this, [=]()
            {
        state->setOutput(ui->stateOutputLineEdit->text());
        qDebug() << state->getOutput(); });

    // Display conditions
    for (auto *row : selectedState->getTransitionsRows())
    {
        ui->conditionsLayout->addWidget(row);
        row->show(); // make visible again
    }

    // Add new condition to new transition
    disconnect(fsmScene, &FSMScene::addNewTransition, nullptr, nullptr);
    connect(fsmScene, &FSMScene::addNewTransition, this, [=](FSMTransition *transition)
            {
        auto row = onAddTransitionClicked();
        auto edit = row->getToStateEdit();
        edit->setText(transition->getSecondState()->getLabel());;
        edit->setReadOnly(true);
        row->setTransitionItem(transition);
        transition->setRow(row);
    });

    // Save conditions
    // disconnect(ui->saveConditionsButton, &QPushButton::clicked, nullptr, nullptr);
    // connect(ui->saveConditionsButton, &QPushButton::clicked, this, [state, this]() {
    //     state->saveConditions(selectedState->getTransitionsRows());
    // });
}

// CONDITIONS
TransitionRowWidget *MainWindow::onAddTransitionClicked()
{
    auto *row = new TransitionRowWidget();

    ui->conditionsLayout->addWidget(row);

    connect(row, &TransitionRowWidget::requestCreate, this, &MainWindow::onCreateTransition);
    connect(row, &TransitionRowWidget::requestRemove, this, &MainWindow::onRemoveTransition);

    selectedState->getTransitionsRows().append(row);

    return row;
}

void MainWindow::onCreateTransition(TransitionRowWidget *row)
{
    if (row->getConditionText().isEmpty() || row->getToStateText().isEmpty())
    {
        qDebug() << "Please provide transition details";
        return;
    }

    QString toStateLabel = row->getToStateText();

    if (!fsmScene->getFSMStates().contains(toStateLabel))
    {
        qDebug() << "State " << toStateLabel << "does not exist";
        row->getToStateEdit()->clear();
    }
    else
    {
        if (!row->getTransitionItem())
        {
            FSMState *toState = fsmScene->getFSMStates().value(toStateLabel);
            auto transition = fsmScene->createTransition(selectedState, toState);
            row->setTransitionItem(transition);
            transition->setRow(row);
        }

        // selectedState->saveConditions(selectedState->getTransitionsRows());
    }
}

void MainWindow::onRemoveTransition(TransitionRowWidget *row)
{
    auto transition = row->getTransitionItem();
    if (transition && fsmScene->getTransitions().contains(transition))
    {
        fsmScene->deleteTransition(transition);
    }
    ui->conditionsLayout->removeWidget(row);
    selectedState->m_transitionsRows.removeAll(row);
    row->setTransitionItem(nullptr);
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

void MainWindow::detachWidgetsFromLayout(QLayout *layout)
{
    while (QLayoutItem *item = layout->takeAt(0))
    {
        if (QWidget *widget = item->widget())
        {
            widget->setParent(nullptr); // safely detach from layout
            widget->hide();             // hide so it's not visible until needed
        }
        delete item; // delete the QLayoutItem, not the widget
    }
}

void MainWindow::clearFSMDetails() {
    ui->automataNameLineEdit->clear();
    ui->automataDescriptionTextEdit->clear();

    for (auto row : inputsWidgets) {
        if (row) {
            inputsLayout->removeWidget(row);
            row->deleteLater();
        }
    }

    inputsWidgets.clear();

    for (auto row : outputsWidgets) {
        if (row) {
            outputsLayout->removeWidget(row);
            row->deleteLater();
        }
    }

    outputsWidgets.clear();

    for (auto row : variablesWidgets) {
        if (row) {
            variablesLayout->removeWidget(row);
            row->deleteLater();
        }
    }

    variablesWidgets.clear();
}

void MainWindow::clearTransitionRows()
{
    selectedState->getTransitionsRows().clear();
}
