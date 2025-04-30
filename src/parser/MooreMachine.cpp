#include "MooreMachine.h"

MooreMachine::MooreMachine(const QString &name, const QString &comment)
    : automate_name(name), automate_comment(comment) {}

void MooreMachine::setName(const QString &name)
{
    automate_name = name;
}

void MooreMachine::setComment(const QString &comment)
{
    automate_comment = comment;
}

const QString &MooreMachine::getName() const
{
    return automate_name;
}

const QString &MooreMachine::getComment() const
{
    return automate_comment;
}

void MooreMachine::addState(const QString &name, const std::shared_ptr<MooreState> &state)
{
    states.insert(name, state);
}

std::shared_ptr<MooreState> MooreMachine::getState(const QString &name)
{
    return states.value(name, nullptr);
}
