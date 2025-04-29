#pragma once
#include <string>

class IMooreState
{
public:
    virtual ~IMooreState() = default;
    virtual std::string getName() const = 0;
    virtual std::string getOutput() const = 0;
    virtual void addTransition(char input, IMooreState *target) = 0;
    virtual IMooreState *getNextState(char input) const = 0;
};