#include "MooreMachineExecutor.h"
MachineExecutor::MachineExecutor(MooreMachine *machine)
    : machine(machine), currentState(nullptr)
{
}
void MachineExecutor::SetStrategy(IExecutionStrategy *strategy)
{
    strategy_ = strategy;
}

void MachineExecutor::Execute(Automaton &automaton)
{
    if (strategy_)
    {
        strategy_->Execute(automaton);
    }
}
