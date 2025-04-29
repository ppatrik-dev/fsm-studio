#include "MooreMachine.h"

MooreMachine::MooreMachine(const std::string &name, const std::string &comment)
    : automate_name(name), automate_comment(comment) {}

void MooreMachine::setName(const std::string &name)
{
    automate_name = name;
}

void MooreMachine::setComment(const std::string &comment)
{
    automate_comment = comment;
}

const std::string &MooreMachine::getName() const
{
    return automate_name;
}

const std::string &MooreMachine::getComment() const
{
    return automate_comment;
}

void MooreMachine::addState(const std::string &name, const std::shared_ptr<MooreState> &state)
{
    states[name] = state;
}

std::shared_ptr<MooreState> MooreMachine::getState(const std::string &name)
{
    return states[name];
}
