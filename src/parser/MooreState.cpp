#include "MooreState.h"

MooreState::MooreState(const std::string &name, const std::string &output, bool is_end_state)
    : name(name), output(output), is_end_state(is_end_state)
{
}

std::string MooreState::getName() const
{
    return name;
}

std::string MooreState::getOutput() const
{
    return output;
}

bool MooreState::isFinal()
{
    return is_end_state;
}

void MooreState::addTransition(char input, IMooreState *target)
{
    transitions[input] = target;
}

IMooreState *MooreState::getNextState(char input) const
{
    auto it = transitions.find(input);
    return it != transitions.end() ? it->second : nullptr;
}
