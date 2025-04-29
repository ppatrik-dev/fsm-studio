#pragma once

#include "IMooreState.h"
#include <map>
#include <string>

class MooreState : public IMooreState
{
    std::string name;
    std::string output;
    bool is_end_state;
    std::map<char, IMooreState *> transitions;

public:
    MooreState(const std::string &name, const std::string &output, bool is_end_state = false);

    std::string getName() const override;
    std::string getOutput() const override;
    bool isFinal();
    void addTransition(char input, IMooreState *target) override;
    IMooreState *getNextState(char input) const override;
};
