/**
 * @file StepExecutionStrategy.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
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
 * @brief Class for execution in steps
 */
class StepExecutionStrategy : public QObject, public IExecutionStrategy
{
    Q_OBJECT

    /// @brief
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

    /**
     * @brief
     *
     * @return * void
     */
    void Execute() override;

    /**
     * @brief
     *
     * @param message
     * @param type
     */
    void terminalLog(QString message, MessageType type);

    /**
     * @brief
     *
     */
    void initializeVariables();
    /**
     * @brief
     *
     */
    void executeStateOutput();
    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool evaluateTransitions();
    /**
     * @brief
     *
     */
    void finalizeExecution();
    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool isFinished() const { return m_finished; }
    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool allStacksAreEmpty();
    /**
     * @brief
     *
     */
    void outputVariables();

private:
    /// @brief
    QString m_output;
    /// @brief
    bool m_finished = false;
    /// @brief
    std::shared_ptr<MooreState> m_currentState;
    /// @brief
    ActionExecutor &m_actionExecutor;
    /// @brief
    MooreMachine &m_mooreMachine;
    /// @brief
    QVector<QString> m_input;
    /// @brief
    qint32 index;
    /// @brief
    QMap<QString, QStack<QString>> inputStacks;
public slots:
    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool step();
    /**
     * @brief
     *
     */
    void reset();
signals:
    /**
     * @brief
     *
     * @param type
     * @param content
     */
    void sendMessage(QString type, QString content);
    /**
     * @brief
     *
     * @param name
     */
    void currentStateChanged(QString name);
    /**
     * @brief
     *
     * @param varName
     * @param remainingInput
     */
    void sendRemainingInput(QString varName, QString remainingInput);
    /**
     * @brief
     *
     * @param varName
     * @param remainingInput
     */
    void sendRemainingOutput(QString varName, QString remainingInput);
    /**
     * @brief
     *
     * @param varName
     * @param remainingInput
     */
    void sendRemainingVariable(QString varName, QString remainingInput);
    /**
     * @brief
     *
     */
    void endOfSimulation();
};