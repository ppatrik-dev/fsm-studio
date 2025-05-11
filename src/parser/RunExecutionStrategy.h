/**
 * @file RunExecutionStrategy.h
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
#include <QTimer>
#include <QString>
#include <QObject>

/**
 * @brief
 *
 */
class RunExecutionStrategy : public QObject, public IExecutionStrategy
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
     * @brief Construct a new Run Execution Strategy object
     *
     * @param actionExecutor
     * @param mooreMachine
     * @param parent
     */
    explicit RunExecutionStrategy(ActionExecutor &actionExecutor,
                                  MooreMachine &mooreMachine,
                                  QObject *parent = nullptr);
    /**
     * @brief
     *
     */
    void Execute() override;
    /**
     * @brief Stepping in simulation
     *
     * @param state
     * @return true
     * @return false
     */
    bool step(std::shared_ptr<MooreState> state);
    /**
     * @brief Creating messages for Terminal Gui
     *
     * @param message
     * @param type
     */
    void terminalLog(QString message, MessageType type);
    /**
     * @brief Getting values of the variables from QJSEngine and printing them
     *
     */
    void outputVariables();

private:
    QString output;
    std::shared_ptr<MooreState> currentState;
    ActionExecutor &actionExecutor;
    MooreMachine &mooreMachine;

signals:
    /**
     * @brief sending message to GUI
     *
     * @param type
     * @param content
     */
    void sendMessage(QString type, QString content);
};
