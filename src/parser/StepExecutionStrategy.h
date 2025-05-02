#pragma once

#include "MooreMachine.h"

class StepExecutionStrategy : public IExecutionStrategy
{
public:
    void Execute(MooreMachine &machine) override;
};
