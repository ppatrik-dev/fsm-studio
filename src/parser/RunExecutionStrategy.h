#pragma once

#include "IExecutionStrategy.h"
#include "MooreMachine.h"

class RunExecutionStrategy : public IExecutionStrategy
{
public:
    void Execute(MooreMachine &automaton) override;
    bool step(std::shared_ptr<MooreState> state, ActionExecutor &engine);

private:
    MooreMachine *machine;
    MooreState *currentState;
    QString output;
};
