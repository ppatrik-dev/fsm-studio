#pragma once

#include "MooreMachine.h"
#include "IExecutionStrategy.h"

class StepExecutionStrategy : public IExecutionStrategy
{
public:
    void Execute() override;

private:
    QString output;
};
