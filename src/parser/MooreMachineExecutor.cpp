/**
 * @file MooreMachineExecutor.cpp
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "MooreMachineExecutor.h"

/**
 * @brief Construct a new Machine Executor:: Machine Executor object
 *
 * @param machine
 * @param parent
 */
MachineExecutor::MachineExecutor(MooreMachine *machine, QObject *parent)
    : QObject(parent),
      strategy_(nullptr),
      machine(machine),
      currentState(nullptr)
{
}

void MachineExecutor::SetStrategy(IExecutionStrategy *strategy)
{
    strategy_ = strategy;
}

void MachineExecutor::Execute()
{
    if (strategy_)
    {
        strategy_->Execute();
    }
}
