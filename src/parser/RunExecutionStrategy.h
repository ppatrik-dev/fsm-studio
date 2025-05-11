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
     * @brief
     *
     * @param state
     * @return true
     * @return false
     */
    bool step(std::shared_ptr<MooreState> state);
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
    void outputVariables();

private:
    /// @brief
    QString output;
    /// @brief
    std::shared_ptr<MooreState> currentState;
    /// @brief
    ActionExecutor &actionExecutor;
    /// @brief
    MooreMachine &mooreMachine;

signals:
    /**
     * @brief
     *
     * @param type
     * @param content
     */
    void sendMessage(QString type, QString content);
};
