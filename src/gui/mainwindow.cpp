/**
 * @file mainwindow.h
 * @author Patrik Prochazka, xprochp00
 *         Filip Ficka, xfickaf00
 *         Miroslav Basista (xbasism00@vutbr.cz)
 * @brief cpp file for functions from mainwindow.h
 * @version 1.7
 * @date 2025-05-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FSMView.h"
#include "FSMScene.h"
#include "../parser/AutomateJsonDocument.h"
#include "../parser/RunExecutionStrategy.h"
#include "../parser/IExecutionStrategy.h"
#include "../parser/MooreMachine.h"
#include "../parser/MooreMachineExecutor.h"
#include "TransitionRowWidget.h"
#include "FSMState.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include "../parser/StepExecutionStrategy.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fsmView = ui->fsmGraphicsView;
    fsmScene = new FSMScene(this);
    fsmView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    fsmView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    fsmView->setScene(fsmScene);
    machine = new MooreMachine(this);
    fsmScene->setMachine(machine);
    fsmScene->addConnects();
    fsmGui = new FSMGui(fsmScene);

    FSMState::m_layout = ui->conditionsLayout;

    connect(ui->fsmGraphicsView, &FSMView::zoomChanged, this, [=](int percent)
            { ui->zoomLabel->setText(QString::number(percent) + "%"); });

    AutomateJsonDocument *jsonDocument = new AutomateJsonDocument(this);

    // terminal creation

    ui->TerminalScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->TerminalScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    terminal = new TerminalWidget();
    ui->TerminalScrollArea->setWidget(terminal);
    ui->TerminalScrollArea->setWidgetResizable(true);

    connect(terminal, &TerminalWidget::lineAppended, this, [=]()
            { QTimer::singleShot(0, this, [=]()
                                 { QTimer::singleShot(0, this, [=]()
                                                      {
                auto scroll = ui->TerminalScrollArea->verticalScrollBar();
                scroll->setValue(scroll->maximum()); }); }); });

    ui->TerminalReset->setEnabled(false);
    ui->TerminalReset->setStyleSheet(disableStyle);
    connect(ui->TerminalRun, &QPushButton::clicked, this, &MainWindow::on_TerminalRun_clicked);
    connect(ui->TerminalReset, &QPushButton::clicked, this, &MainWindow::on_TerminalReset_clicked);

    connect(ui->TerminalRun, &QPushButton::clicked, this, &MainWindow::toggleCancel);

    connect(this, &MainWindow::loadJsonRequested, jsonDocument, &AutomateJsonDocument::loadAutomateFromJsonFile);
    connect(this, &MainWindow::exportJsonRequested, jsonDocument, &AutomateJsonDocument::saveAutomateToJsonFile);
    connect(this, &MainWindow::createMachine, fsmScene, &FSMScene::createMachineFile);
    connect(this, &MainWindow::clearMachineRequested, machine, &MooreMachine::clearMachine);
    connect(this, &MainWindow::clearSceneRequested, fsmScene, &FSMScene::onClearScene);
    connect(this, &MainWindow::importDetailsRequested, fsmGui, &FSMGui::importDetails);
    connect(fsmGui, &FSMGui::displayDetailsRequested, this, &MainWindow::displayFSMDetais);
    connect(fsmGui, &FSMGui::displayUpdatedInputRequested, this, &MainWindow::displayUpdatedInput);
    connect(fsmGui, &FSMGui::displayUpdatedOutputRequested, this, &MainWindow::displayUpdatedOutput);
    connect(fsmGui, &FSMGui::displayUpdatedVariableRequested, this, &MainWindow::displayUpdatedVariable);

    // Control buttons
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::onImportFileClicked);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::onExportFileClicked);
    connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::startSimulation);
    connect(fsmGui, &FSMGui::inputAddValue, machine, &MooreMachine::addGuiInput);
    connect(fsmGui, &FSMGui::inputDeleteValue, machine, &MooreMachine::deleteGuiInput);
    connect(fsmGui, &FSMGui::outputAddValue, machine, &MooreMachine::addGuiOutput);
    connect(fsmGui, &FSMGui::outputDeleteValue, machine, &MooreMachine::deleteGuiOutput);
    connect(fsmGui, &FSMGui::variableAddValue, machine, &MooreMachine::addGuiVariable);
    connect(fsmGui, &FSMGui::variableDeleteValue, machine, &MooreMachine::deleteGuiVariable);

    connect(ui->TerminalClear, &QPushButton::clicked, this, [=]()
            { terminal->clearTerminal(); });

    connect(ui->TerminalCancel, &QPushButton::clicked, this, &MainWindow::cancelSimulation);
    connect(ui->TerminalRun, &QPushButton::clicked, this, &MainWindow::runSimulation);

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

    connect(fsmScene, &FSMScene::newTransitionRowRequested, this, &MainWindow::newTransitionRow);
    connect(fsmScene, &FSMScene::requestRemoveRowAndTransition, this, &MainWindow::removeRowAndTransition);
}
void MainWindow::startSimulation()
{
    if (selectedState)
        selectedState->setSelected(false);

    if (!fsmGui->getInitialState())
    {
        qWarning() << "Initial state not selected";
        return;
    }

    fsmScene->removeEpsilonTransitions();
    toggleTerminal();

    if (machine != nullptr)
    {
        moore = new MooreJs(this);
        actionExecute = new ActionExecutor(this);
        actionExecute->exposeObject("moore", moore);

        executor = new MachineExecutor(machine, this);
        stepStrategy = new StepExecutionStrategy(*actionExecute, *machine, this);

        connect(this, &MainWindow::setStrategy, executor, &MachineExecutor::SetStrategy);
        connect(this, &MainWindow::executeMachine, executor, &MachineExecutor::Execute);
        connect(stepStrategy, &StepExecutionStrategy::sendMessage, terminal, &TerminalWidget::receiveMessage);
        connect(stepStrategy, &StepExecutionStrategy::currentStateChanged, fsmScene, &FSMScene::setActiveState);
        connect(stepStrategy, &StepExecutionStrategy::sendRemainingInput, fsmGui, &FSMGui::updateInput);
        connect(stepStrategy, &StepExecutionStrategy::sendRemainingOutput, fsmGui, &FSMGui::updateOutput);
        connect(stepStrategy, &StepExecutionStrategy::sendRemainingVariable, fsmGui, &FSMGui::updateVariable);
        connect(ui->TerminalReset, &QPushButton::clicked, stepStrategy, &StepExecutionStrategy::reset);
        connect(stepStrategy, &StepExecutionStrategy::endOfSimulation, this, &MainWindow::toggleCancel);
        emit setStrategy(stepStrategy);
    }
    else
    {
        qDebug() << "Machine is null, Create automate!";
    }
}

void MainWindow::cancelSimulation()
{
    toggleTerminal();
    fsmScene->unsetActiveState();

    if (stepStrategy)
    {
        stepStrategy->deleteLater();
        stepStrategy = nullptr;
    }
    if (executor)
    {
        executor->deleteLater();
        executor = nullptr;
    }
    if (actionExecute)
    {
        actionExecute->deleteLater();
        actionExecute = nullptr;
    }
    if (moore)
    {
        moore->deleteLater();
        moore = nullptr;
    }
}

void MainWindow::runSimulation()
{
    emit executeMachine(*machine);
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
    clear();
    emit loadJsonRequested(filename, *machine);
    emit createMachine(*machine);
    emit importDetailsRequested();
}

GenericRowWidget *MainWindow::createDetailsRow(QVBoxLayout *layout, QList<GenericRowWidget *> &widgets, GenericRowWidget::RowType type)
{
    GenericRowWidget *row = new GenericRowWidget(type, this);
    layout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, &MainWindow::onDeleteRow);

    widgets.append(row);

    return row;
}

void MainWindow::displayUpdatedDetail(detailTypeEnum type, QString key, QString value)
{
    QVBoxLayout *layout = nullptr;

    switch (type)
    {
    case INPUT_DETAIL:
        layout = inputsLayout;
        break;
    case OUTPUT_DETAIL:
        layout = outputsLayout;
        break;
    case VARIABLE_DETAIL:
        layout = variablesLayout;
        break;
    }

    for (int i = 0; i < layout->count(); ++i)
    {
        QLayoutItem *item = layout->itemAt(i);
        if (!item)
            continue;

        QWidget *widget = item->widget();
        if (!widget)
            continue;

        GenericRowWidget *row = qobject_cast<GenericRowWidget *>(widget);
        if (row && row->getKey() == key)
        {
            row->setValue(value);
            return;
        }
    }
}

void MainWindow::displayUpdatedInput(QString key, QString value)
{
    displayUpdatedDetail(INPUT_DETAIL, key, value);
}

void MainWindow::displayUpdatedOutput(QString key, QString value)
{
    displayUpdatedDetail(OUTPUT_DETAIL, key, value);
}

void MainWindow::displayUpdatedVariable(QString key, QString value)
{
    displayUpdatedDetail(VARIABLE_DETAIL, key, value);
}

void MainWindow::displayFSMDetais()
{
    ui->automataNameLineEdit->setText(fsmGui->getName());
    ui->automataDescriptionTextEdit->setText(fsmGui->getDescription());

    for (const QString &key : fsmGui->getInputs().keys())
    {
        GenericRowWidget *row = createDetailsRow(inputsLayout, inputsWidgets, GenericRowWidget::Input);
        row->setGenericTexts(key, fsmGui->getInputs().value(key));
    }

    for (const QString &key : fsmGui->getOutputs().keys())
    {
        GenericRowWidget *row = createDetailsRow(outputsLayout, outputsWidgets, GenericRowWidget::Output);
        row->setGenericTexts(key, fsmGui->getOutputs().value(key));
    }

    for (const QString &key : fsmGui->getVariables().keys())
    {
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

        if (selectedState)
        {
            selectedState = nullptr;
        }

        return;
    }

    detachWidgetsFromLayout();
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
            { state->updateOutput(ui->stateOutputLineEdit->text()); });

    // Display conditions
    for (auto *row : selectedState->getTransitionsRows())
    {
        ui->conditionsLayout->addWidget(row);
        row->show();
    }

    // Add new condition to new transition
    disconnect(fsmScene, &FSMScene::addNewTransition, nullptr, nullptr);
    connect(fsmScene, &FSMScene::addNewTransition, this, [=](FSMTransition *transition)
            {
        auto row = onAddTransitionClicked();
        auto edit = row->getToStateEdit();
        edit->setText(transition->getSecondState()->getLabel());;
        edit->setReadOnly(true);
        row->disableCreateButton(disableStyle);

        row->setTransitionItem(transition);
        transition->setRow(row); });

    // Save conditions
    disconnect(ui->saveConditionsButton, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->saveConditionsButton, &QPushButton::clicked, this, [state, this]()
            { fsmScene->saveConditions(state); });
}

void MainWindow::newTransitionRow(FSMState *state, TransitionRowWidget *&row)
{
    setSelectedState(state);

    row = onAddTransitionClicked();

    setSelectedState(nullptr);
}

void MainWindow::removeRowAndTransition(FSMState *state, TransitionRowWidget *row)
{
    setSelectedState(state);

    onRemoveTransition(row);

    setSelectedState(nullptr);
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
    if (row->getToStateText().isEmpty())
    {
        qDebug() << "Please provide transition to state";
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
            row->disableCreateButton(disableStyle);
            row->setTransitionItem(transition);
            transition->setRow(row);
        }
    }
}

void MainWindow::onRemoveTransition(TransitionRowWidget *row)
{
    auto transition = row->getTransitionItem();
    if (transition && fsmScene->getTransitions().contains(transition))
    {
        fsmScene->deleteTransition(transition, true);
    }
    ui->conditionsLayout->removeWidget(row);
    selectedState->getTransitionsRows().removeAll(row);
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
        fsmGui->deleteInput(row->getKey());
    }
    else if (outputsLayout->indexOf(row) != -1)
    {
        outputsLayout->removeWidget(row);
        outputsWidgets.removeAll(row);
        fsmGui->deleteOutput(row->getKey());
    }
    else if (variablesLayout->indexOf(row) != -1)
    {
        variablesLayout->removeWidget(row);
        variablesWidgets.removeAll(row);
        fsmGui->deleteVariable(row->getKey());
    }

    row->deleteLater();
}

void MainWindow::detachWidgetsFromLayout()
{
    while (QLayoutItem *item = ui->conditionsLayout->takeAt(0))
    {
        if (QWidget *widget = item->widget())
        {
            widget->setParent(nullptr); // safely detach from layout
            widget->hide();             // hide so it's not visible until needed
        }
        delete item; // delete the QLayoutItem, not the widget
    }
}

void MainWindow::clearFSMDetails()
{
    ui->automataNameLineEdit->clear();
    ui->automataDescriptionTextEdit->clear();

    for (auto row : inputsWidgets)
    {
        if (row)
        {
            inputsLayout->removeWidget(row);
            row->deleteLater();
        }
    }

    inputsWidgets.clear();

    for (auto row : outputsWidgets)
    {
        if (row)
        {
            outputsLayout->removeWidget(row);
            row->deleteLater();
        }
    }

    outputsWidgets.clear();

    for (auto row : variablesWidgets)
    {
        if (row)
        {
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

// function for diseabling delete buttons in genericRow
void MainWindow::setDeleteButtonsEnabled(bool enabled)
{
    for (GenericRowWidget *row : inputsWidgets)
    {
        row->setDeleteButtonEnabled(enabled);
    }
    for (GenericRowWidget *row : outputsWidgets)
    {
        row->setDeleteButtonEnabled(enabled);
    }
    for (GenericRowWidget *row : variablesWidgets)
    {
        row->setDeleteButtonEnabled(enabled);
    }
}

void MainWindow::toggleCancel()
{

    if (!inSimulation)
    {
        ui->TerminalCancel->setEnabled(false);
        this->inSimulation = true;
    }

    else
    {
        ui->TerminalCancel->setEnabled(true);
        ui->TerminalReset->setEnabled(true);
        ui->TerminalReset->setStyleSheet("");
        this->inSimulation = false;
    }
}

// function for terminal set up
void MainWindow::toggleTerminal()
{

    // diseabling buttons and changing colors for button run
    if (!TerminalActive)
    {

        ui->detailsPanel->setCurrentWidget(ui->automataPropertiesPanel);
        TerminalActive = true;

        ui->runButton->setEnabled(false);
        ui->importButton->setEnabled(false);
        ui->exportButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->addInputButton->setEnabled(false);
        ui->addOutputButton->setEnabled(false);
        ui->addVariableButton->setEnabled(false);
        setDeleteButtonsEnabled(false);

        ui->runButton->setStyleSheet(disableStyle);
        ui->importButton->setStyleSheet(disableStyle);
        ui->exportButton->setStyleSheet(disableStyle);
        ui->clearButton->setStyleSheet(disableStyle);
        ui->addInputButton->setStyleSheet(disableStyle);
        ui->addOutputButton->setStyleSheet(disableStyle);
        ui->addVariableButton->setStyleSheet(disableStyle);

        ui->fsmGraphicsView->setEnabled(false);

        ui->runButton->setStyleSheet(
            "QPushButton {"
            " background-color: #228B22;" // ForestGreen
            " color: white;"
            " border: 1px solid #1e7b1e;"
            " border-radius: 6px;"
            " padding: 6px 12px;"
            " }"
            "QPushButton:hover {"
            " background-color: #2ecc71;"
            " }"
            "QPushButton:pressed {"
            " background-color: #1e6821;"
            " }");

        terminal->appendLine("[TERMINAL] Started simulation...", PURPLE);
    }

    else
    {

        fsmView->restorePreviousView();
        on_TerminalReset_clicked();

        TerminalActive = false;

        ui->runButton->setEnabled(true);
        ui->importButton->setEnabled(true);
        ui->exportButton->setEnabled(true);
        ui->clearButton->setEnabled(true);
        ui->addInputButton->setEnabled(true);
        ui->addOutputButton->setEnabled(true);
        ui->addVariableButton->setEnabled(true);
        setDeleteButtonsEnabled(true);

        ui->runButton->setStyleSheet("");
        ui->importButton->setStyleSheet("");
        ui->exportButton->setStyleSheet("");
        ui->clearButton->setStyleSheet("");
        ui->addInputButton->setStyleSheet("");
        ui->addOutputButton->setStyleSheet("");
        ui->addVariableButton->setStyleSheet("");

        ui->fsmGraphicsView->setEnabled(true);

        terminal->clearTerminal();
        ui->runButton->setStyleSheet("");
    }

    // get height, set new and animate
    int currentHeight = ui->TerminalFrame->maximumHeight();
    int targetHeight = currentHeight == 0 ? 300 : 0;

    QPropertyAnimation *animation = new QPropertyAnimation(ui->TerminalFrame, "maximumHeight");
    animation->setDuration(300);
    animation->setStartValue(currentHeight);
    animation->setEndValue(targetHeight);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    if (TerminalActive)
    {

        connect(animation, &QPropertyAnimation::finished, this, [this]()
                {
            fsmView->fitToSceneOnce();
            terminal->lineAppended(); });
    }

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::on_TerminalRun_clicked()
{
    ui->TerminalRun->setEnabled(false);

    ui->TerminalRun->setStyleSheet(disableStyle);
}

void MainWindow::on_TerminalReset_clicked()
{
    ui->TerminalRun->setEnabled(true);
    ui->TerminalReset->setEnabled(false);

    ui->TerminalRun->setStyleSheet("");
    ui->TerminalReset->setStyleSheet(disableStyle);
}
