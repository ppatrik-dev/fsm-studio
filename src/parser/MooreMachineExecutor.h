#pragma once

#include "IExecutionStrategy.h"

class MachineExecutor
{
public:
    MachineExecutor(MooreMachine *machine);
    void SetStrategy(IExecutionStrategy *strategy);
    void Execute(MooreMachine &machine);

private:
    IExecutionStrategy *strategy_ = nullptr;
    MooreMachine *machine;
    MooreState *currentState;
    QString output;
};
