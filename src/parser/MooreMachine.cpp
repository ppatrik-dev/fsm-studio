#include "MooreMachine.h"

MooreMachine::MooreMachine(const std::string &name, const std::string &comment)
    : automate_name(name), automate_comment(comment)
{
}

void MooreMachine::addState(const std::string &name, const std::shared_ptr<MooreState> &state)
{
    states[name] = state;
}

std::shared_ptr<MooreState> MooreMachine::getState(const std::string &name)
{
    auto it = states.find(name);
    if (it != states.end())
    {
        return it->second;
    }
    return nullptr;
}
