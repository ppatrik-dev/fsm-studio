/**
 * @file MooreMachineExecutor.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Header file for the MachineExecutor class, responsible for executing a Moore machine using a pluggable execution strategy
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
 * @class MachineExecutor
 * @brief Controls the execution of a Moore machine using a strategy pattern.
 */
class MachineExecutor : public QObject
{
    Q_OBJECT
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
     * @brief Start simulation
     *
     */
    void Execute();

private:
    IExecutionStrategy *strategy_ = nullptr;
    MooreMachine *machine;
    MooreState *currentState;
    QString output;
};
