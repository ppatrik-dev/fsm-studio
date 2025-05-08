#include "MooreMachineExecutor.h"
MachineExecutor::MachineExecutor(MooreMachine *machine, QObject *parent)
    : QObject(parent), machine(machine), currentState(nullptr), strategy_(nullptr)
{
}
void MachineExecutor::SetStrategy(IExecutionStrategy *strategy)
{
    strategy_ = strategy;
}

void MachineExecutor::Execute(MooreMachine &machine)
{
    if (strategy_)
    {
        strategy_->Execute(machine);
    }
}
