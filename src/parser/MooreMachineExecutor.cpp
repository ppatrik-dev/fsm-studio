#include "MooreMachineExecutor.h"
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
