#pragma once

#include "MooreMachine.h"
#include "ActionExecutor.h" // nezabudni pridať

class MooreSimulator
{
public:
    MooreSimulator(MooreMachine *machine);
    bool run();
    bool step(std::shared_ptr<MooreState> state, ActionExecutor &engine);

private:
    MooreMachine *machine;
    MooreState *currentState;
    QString output;
};
