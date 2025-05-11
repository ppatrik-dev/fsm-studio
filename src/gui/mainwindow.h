/**
 * @file mainwindow.h
 * @author Patrik Prochazka (xprochp00@vutbr.cz)
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @author Filip Ficka, xfickaf00
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

/**
 * @brief MainWindow class, inherit from QMainWindow
 * 
 */
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
    /**
     * @brief Clear application save data
     * 
     */
    void clear()
    {
        emit clearSceneRequested();
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

    /// @brief  layouts for rows
    QVBoxLayout *inputsLayout;
    QVBoxLayout *outputsLayout;
    QVBoxLayout *variablesLayout;

    /// @brief  lists for tracking row widgets
    QList<GenericRowWidget *> inputsWidgets;
    QList<GenericRowWidget *> outputsWidgets;
    QList<GenericRowWidget *> variablesWidgets;
    ActionExecutor *actionExecute = nullptr;
    MachineExecutor *executor = nullptr;
    StepExecutionStrategy *stepStrategy = nullptr;
    MooreJs *moore = nullptr;

    TerminalWidget *terminal;
    bool TerminalActive = false;
    bool inSimulation = false;
    QString disableStyle = "QPushButton:disabled { background-color: #444444; color: #888888; }";

    /**
     * @brief Enumeration for FSM detail type
     * 
     */
    enum detailTypeEnum
    {
        INPUT_DETAIL,
        OUTPUT_DETAIL,
        VARIABLE_DETAIL
    };

    detailTypeEnum detailType;

signals:
    void loadJsonRequested(const QString &fileName, MooreMachine &machine);
    void exportJsonRequested(const QString &fileName, MooreMachine &machine);
    void createMachine(MooreMachine &machine);
    void clearMachineRequested();
    void clearSceneRequested();
    void importDetailsRequested();
    void setStrategy(IExecutionStrategy *strategy);
    void executeMachine(MooreMachine &machine);
    void resetSimulation();

public slots:
    TransitionRowWidget *onAddTransitionClicked();
    void newTransitionRow(FSMState *state, TransitionRowWidget *&row);
    void removeRowAndTransition(FSMState *state, TransitionRowWidget *row);
    void displayUpdatedInput(QString key, QString value);
    void displayUpdatedOutput(QString key, QString value);
    void displayUpdatedVariable(QString key, QString value);

private slots:
    /**
     * @brief Run simulation button slot
     * 
     */
    void runSimulation();

    /**
     * @brief Start simulation button slot
     * 
     */
    void startSimulation();

    /**
     * @brief Cancel simulation button slot
     * 
     */
    void cancelSimulation();

    /**
     * @brief Create new transition object in scene from row
     * 
     * @param row 
     */
    void onCreateTransition(TransitionRowWidget *row);

    /**
     * @brief Delete transition object in scene from row
     * 
     * @param row 
     */
    void onRemoveTransition(TransitionRowWidget *row);

    /**
     * @brief creating of input row 
     * binded into add button
     * 
     */
    void onAddInputClicked();

    /**
     * @brief creating of output row 
     * binded into add button
     * 
     */
    void onAddOutputClicked();

    /**
     * @brief creating of variable row 
     * binded into add button
     * 
     */
    void onAddVariableClicked();

    /**
     * @brief function for deleting
     * 
     * @param row 
     */
    void onDeleteRow(GenericRowWidget *row);

    void onImportFileClicked();
    void onExportFileClicked();
    void showDetailsPanel(QGraphicsItem *item);

    /**
     * @brief function to open and close terminal
     * binded to runButton
     * 
     */
    void toggleTerminal();

    /**
     * @brief function for disabling cancel
     * binded to TerminalRun button
     * 
     */
    void toggleCancel();

    /**
     * @brief function for diseabling delete buttons in genericRow
     * 
     * @param enabled 
     */
    void setDeleteButtonsEnabled(bool enabled);

    void displayFSMDetais();

    /**
     * @brief function for terminalRun button
     * setting bools and disabling buttons
     * 
     */
    void on_TerminalRun_clicked();

    /**
     * @brief function for terminalReset button
     * setting bools and enabling buttons
     * 
     */
    void on_TerminalReset_clicked();

public:
    /**
     * @brief Set the Selected State object
     * 
     * @param state 
     */
    void setSelectedState(FSMState *state)
    {
        selectedState = state;
    }

    /**
     * @brief Create a Details Row object
     * 
     * @param layout 
     * @param widgets 
     * @param type 
     * @return GenericRowWidget* 
     */
    GenericRowWidget *createDetailsRow(QVBoxLayout *layout, QList<GenericRowWidget *> &widgets, GenericRowWidget::RowType type);

private:
    /**
     * @brief Displays updated FSM detail in right panel
     * 
     * @param type 
     * @param key 
     * @param value 
     */
    void displayUpdatedDetail(detailTypeEnum type, QString key, QString value);

    /**
     * @brief Clears stored FSM details
     * 
     */
    void clearFSMDetails();

    /**
     * @brief Clears transition condition rows
     * 
     */
    void clearTransitionRows();

    /**
     * @brief detach row widgets from layout
     * 
     */
    void detachWidgetsFromLayout();
};

#endif // MAINWINDOW_H
