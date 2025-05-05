// File: mainwindow.cpp
// Author: Patrik Prochazka, Filip Ficka
// Login: xprochp00, xfickaf00

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FSMView.h"
#include "FSMScene.h"
#include "FSMState.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fsmView = ui->fsmGraphicsView;
    fsmScene = new FSMScene(this);
    fsmView->setScene(fsmScene);

    fsmGui = new FSMGui(fsmScene);

    // Control buttons
    connect(ui->clearButton, &QPushButton::clicked, fsmScene, &FSMScene::onClearScene);    

    // FSM scale
    connect(ui->fsmGraphicsView, &FSMView::zoomChanged, this, [=](int percent) {
        ui->zoomLabel->setText(QString::number(percent) + "%");
    });

    // FSM editing
    connect(fsmView, &FSMView::addStateRequested, fsmScene, &FSMScene::onAddState);
    connect(fsmView, &FSMView::addTransitionRequested, fsmScene, &FSMScene::onAddTransition);
    connect(fsmView, &FSMView::deleteStateRequested, fsmScene, &FSMScene::onDeleteState);
    connect(fsmView, &FSMView::deleteTransitionRequested, fsmScene, &FSMScene::onDeleteTransition);

    // Details panel
    connect(fsmScene, &FSMScene::itemSelected, this, &MainWindow::showDetailsPanel);

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

    connect(ui->addConditionButton, &QPushButton::clicked, this, [=]() {
        auto *row = new ConditionRowWidget();
        ui->conditionsLayout->addWidget(row);

        connect(row, &ConditionRowWidget::requestDelete, this, [=]() {
            ui->conditionsLayout->removeWidget(row);
            conditionWidgets.removeAll(row);
            row->deleteLater();
        });

        conditionWidgets.append(row);
    });

    // FSM details saving
    connect(ui->automataNameLineEdit, &QLineEdit::editingFinished, this, [=]() {
        fsmGui->saveName(ui->automataNameLineEdit->text());
    });

    connect(ui->saveInputsButton, &QPushButton::clicked, this, [=]() {
        fsmGui->saveInputs(inputsWidgets);
    });

    connect(ui->saveOutputsbutton, &QPushButton::clicked, this, [=]() {
        fsmGui->saveOutputs(outputsWidgets);
    });

    connect(ui->saveVariablesButton, &QPushButton::clicked, this, [=]() {
        fsmGui->saveVariables(variablesWidgets);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// MENU
void MainWindow::showDetailsPanel(QGraphicsItem *item) {
    if (!item || item->type() != FSMState::Type) {
        clearGenericRows();
        ui->detailsPanel->setCurrentWidget(ui->automataPropertiesPanel);

        // Display FSM inputs
        auto inputs = fsmGui->getInputs();
        for (const QString &key : inputs.keys()) {
            QString value = inputs.value(key);

            auto row = createGenericRow(inputsLayout, inputsWidgets, GenericRowWidget::Input);
            row->setGenericTexts(key, value);
        }

        // Display FSM outputs
        auto outputs = fsmGui->getOutputs();
        for (const QString &key : outputs.keys()) {
            QString value = outputs.value(key);

            auto row = createGenericRow(outputsLayout, outputsWidgets, GenericRowWidget::Output);
            row->setGenericTexts(key, value);
        }

        // Display FSM variables
        auto variables = fsmGui->getVariables();
        for (const QString &key : variables.keys()) {
            QString value = variables.value(key);

            auto row = createGenericRow(variablesLayout, variablesWidgets, GenericRowWidget::Variable);
            row->setGenericTexts(key, value);
        }
    }

    else if (item->type() == FSMState::Type) {
        clearConditionRows();
        ui->detailsPanel->setCurrentWidget(ui->statePropertiesPanel);

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
}

GenericRowWidget* MainWindow::createGenericRow(QVBoxLayout *layout, QList<GenericRowWidget*> &rows, GenericRowWidget::RowType type) {
    GenericRowWidget *row = new GenericRowWidget(type);

    layout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, &MainWindow::onDeleteRow);

    rows.append(row);

    return row;
}

// INPUTS
void MainWindow::onAddInputClicked() {
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Input);

    inputsLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, &MainWindow::onDeleteRow);

    inputsWidgets.append(row);
}

// OUTPUTS
void MainWindow::onAddOutputClicked() {
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Output);
    outputsLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, &MainWindow::onDeleteRow);

    outputsWidgets.append(row);
}

// VARIABLES
void MainWindow::onAddVariableClicked() {
    GenericRowWidget *row = new GenericRowWidget(GenericRowWidget::Variable);
    variablesLayout->addWidget(row);

    connect(row, &GenericRowWidget::requestDelete, this, &MainWindow::onDeleteRow);

    variablesWidgets.append(row);
}

void MainWindow::onDeleteRow(GenericRowWidget *row) {
    if (!row) return;

    // from which layout it came
    if (inputsLayout->indexOf(row) != -1) {
        inputsLayout->removeWidget(row);
        inputsWidgets.removeAll(row);
    } else if (outputsLayout->indexOf(row) != -1) {
        outputsLayout->removeWidget(row);
        outputsWidgets.removeAll(row);
    } else if (variablesLayout->indexOf(row) != -1) {
        variablesLayout->removeWidget(row);
        variablesWidgets.removeAll(row);
    }

    row->deleteLater();
}

void MainWindow::clearConditionRows() {
    clearWidgetsRows(conditionWidgets);
}

void MainWindow::clearGenericRows() {
    clearWidgetsRows(inputsWidgets);
    clearWidgetsRows(outputsWidgets);
    clearWidgetsRows(variablesWidgets);
}

void MainWindow::displayGenericRow(QList<GenericRowWidget*> rows) {
    for (auto row : rows) {

    }
}

