/**
 * @file mainwindow.h
 * @author Patrik Prochazka, xprochp00
 *         Filip Ficka, xfickaf00
 * @brief header file for mainwindow
 * @version 1.7
 * @date 2025-05-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <QPropertyAnimation>
#include "FSMView.h"
#include "FSMScene.h"
#include "../parser/MooreMachine.h"
#include "../parser/IExecutionStrategy.h"
#include "FSMGui.h"
#include "GenericRowWidget.h"
#include "TransitionRowWidget.h"
#include "TerminalWidget.h"
#include "../parser/MooreMachineExecutor.h"
#include "../parser/RunExecutionStrategy.h"
#include "../parser/StepExecutionStrategy.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow()
    {
        clear();

        delete ui;
        delete fsmScene;
        delete fsmView;
        delete fsmGui;

        delete inputsLayout;
        delete outputsLayout;
        delete variablesLayout;
    }

private:
    void clear()
    {
        emit
            emit
            clearSceneRequested();
        emit clearMachineRequested();
        clearFSMDetails();
    }

private:
    Ui::MainWindow *ui;

    FSMScene *fsmScene;
    MooreMachine *machine;
    FSMView *fsmView;
    FSMGui *fsmGui;

    FSMState *selectedState = nullptr;

    QVBoxLayout *inputsLayout;
    QVBoxLayout *outputsLayout;
    QVBoxLayout *variablesLayout;

    QList<GenericRowWidget *> inputsWidgets;
    QList<GenericRowWidget *> outputsWidgets;
    QList<GenericRowWidget *> variablesWidgets;
    ActionExecutor *actionExecute = nullptr;
    MachineExecutor *executor = nullptr;
    StepExecutionStrategy *stepStrategy = nullptr;
    // QList<TransitionRowWidget *> conditionWidgets;

    TerminalWidget *terminal;
    bool TerminalActive = false;

signals:
    void loadJsonRequested(const QString &fileName, MooreMachine &machine);
    void exportJsonRequested(const QString &fileName, MooreMachine &machine);
    void createMachine(MooreMachine &machine);
    void clearMachineRequested();
    void clearSceneRequested();
    void importDetailsRequested();
    void setStrategy(IExecutionStrategy *strategy);
    void executeMachine(MooreMachine &machine);

public slots:
    TransitionRowWidget *onAddTransitionClicked();
    void newTransitionRow(FSMState *state, TransitionRowWidget *&row);
    void removeRowAndTransition(FSMState *state, TransitionRowWidget *row);

private slots:
    void runSimulation();
    void simulation();
    void onCreateTransition(TransitionRowWidget *row);
    void onRemoveTransition(TransitionRowWidget *row);
    void onAddInputClicked();
    void onAddOutputClicked();
    void onAddVariableClicked();
    void onDeleteRow(GenericRowWidget *row);
    void onImportFileClicked();
    void onExportFileClicked();
    void showDetailsPanel(QGraphicsItem *item);
    void toggleTerminal();
    void setDeleteButtonsEnabled(bool enabled);
    void displayFSMDetais();

public:
    void setSelectedState(FSMState *state)
    {
        selectedState = state;
    }

    GenericRowWidget *createDetailsRow(QVBoxLayout *layout, QList<GenericRowWidget *> &widgets, GenericRowWidget::RowType type);

private:
    void clearFSMDetails();
    void clearTransitionRows();
    void detachWidgetsFromLayout();
};

#endif // MAINWINDOW_H
