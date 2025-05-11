/**
 * @file StepExecutionStrategy.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Header file for the StepExecutionStrategy class, which provides step-by-step execution logic for a Moore machine
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "IExecutionStrategy.h"
#include "MooreMachine.h"
#include "ActionExecutor.h"
#include <QObject>
#include <memory>
#include <QCoreApplication>
#include <QStack>
#include <algorithm>
#include "MooreMachine.h"
#include <QDebug>
#include "MooreJsClass.h"
#include <QTime>
#include <QApplication>

/**
 * @class StepExecutionStrategy
 * @brief Class for executing a Moore machine in discrete steps.
 */
class StepExecutionStrategy : public QObject, public IExecutionStrategy
{
    Q_OBJECT

    /// @brief Type of messages sends to terminal
    enum MessageType
    {
        Error,
        Info,
        TransitionResult,
        Variable,
        Evaluate,
    };

public:
    /**
     * @brief Construct a new Step Execution Strategy object
     *
     * @param actionExecutor
     * @param mooreMachine
     * @param parent
     */
    explicit StepExecutionStrategy(ActionExecutor &actionExecutor,
                                   MooreMachine &mooreMachine,
                                   QObject *parent = nullptr);

private:
    QString m_output;
    bool m_finished = false;
    std::shared_ptr<MooreState> m_currentState;
    ActionExecutor &m_actionExecutor;
    MooreMachine &m_mooreMachine;
    QVector<QString> m_input;
    QMap<QString, QStack<QString>> inputStacks;

    /**
     * @brief Execute Automate
     *
     * @return * void
     */
    void Execute() override;

    /**
     * @brief Creating and sending messages to Gui terminal
     *
     * @param message
     * @param type
     */
    void terminalLog(QString message, MessageType type);

    /**
     * @brief Add all variables (inputs, outputs, variables) to  QJSEngine
     *
     */
    void initializeVariables();
    /**
     * @brief Execute output command
     *
     */
    void executeStateOutput();
    /**
     * @brief Execute transition condition
     *
     * @return true
     * @return false
     */
    bool evaluateTransitions();
    /**
     * @brief Last state procedure (send values of variables to GUI)
     *
     */
    void finalizeExecution();
    /**
     * @brief Simulation finished
     *
     * @return true
     * @return false
     */
    bool isFinished() const { return m_finished; }
    /**
     * @brief Returns true if all stacks in the map are empty.
     *
     * @return true
     * @return false
     */
    bool allStacksAreEmpty();
    /**
     * @brief Get values of variables in QJSEngine and print them
     *
     */
    void outputVariables();
public slots:
    /**
     * @brief Function for stepping in simulation
     *
     * @return true
     * @return false
     */
    bool step();
    /**
     * @brief Function for reseting simulation
     *
     */
    void reset();
signals:
    /**
     * @brief sending message for Gui Terminal
     *
     * @param type
     * @param content
     */
    void sendMessage(QString type, QString content);
    /**
     * @brief sending name of current state to Gui
     *
     * @param name
     */
    void currentStateChanged(QString name);
    /**
     * @brief sending remaining input to Gui
     *
     * @param varName
     * @param remainingInput
     */
    void sendRemainingInput(QString varName, QString remainingInput);
    /**
     * @brief sending remaining output to Gui
     *
     * @param varName
     * @param remainingInput
     */
    void sendRemainingOutput(QString varName, QString remainingInput);
    /**
     * @brief sending remaining variable to Gui
     *
     * @param varName
     * @param remainingInput
     */
    void sendRemainingVariable(QString varName, QString remainingInput);
    /**
     * @brief Notifies the GUI that the simulation has finished
     *
     */
    void endOfSimulation();
};