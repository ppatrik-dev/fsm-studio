#pragma once

#include "IExecutionStrategy.h"
#include "MooreMachine.h"
#include "ActionExecutor.h"

class RunExecutionStrategy : public IExecutionStrategy
{
public:
    void Execute(MooreMachine &machine) override;
    bool step(std::shared_ptr<MooreState> state, ActionExecutor &actionExecute, MooreMachine &machine);

private:
    QString output;
};
