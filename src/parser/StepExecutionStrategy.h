#pragma once

#include "MooreMachine.h"
#include "IExecutionStrategy.h"

class StepExecutionStrategy : public IExecutionStrategy
{
public:
    void Execute(MooreMachine &machine) override;

private:
    QString output;
};
