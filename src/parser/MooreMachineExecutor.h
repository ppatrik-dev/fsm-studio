/**
 * @file MooreMachineExecutor.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <QObject>
#include "IExecutionStrategy.h"
/**
 * @brief
 *
 */
class MachineExecutor : public QObject
{
    Q_OBJECT
    /**
     * @brief
     *
     */
public:
    /**
     * @brief Construct a new Machine Executor object
     *
     * @param machine
     * @param parent
     */
    explicit MachineExecutor(MooreMachine *machine, QObject *parent = nullptr);

public slots:
    /**
     * @brief Set the Strategy object
     *
     * @param strategy
     */
    void SetStrategy(IExecutionStrategy *strategy);
    /**
     * @brief
     *
     */
    void Execute();

private:
    /// @brief
    IExecutionStrategy *strategy_ = nullptr;
    /// @brief
    MooreMachine *machine;
    /// @brief
    MooreState *currentState;
    /// @brief
    QString output;
};
