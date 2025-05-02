#pragma once
#include "MooreMachine.h"

class IExecutionStrategy
{
public:
    virtual ~IExecutionStrategy() = default;
    virtual void Execute(MooreMachine &machine) = 0;
};
