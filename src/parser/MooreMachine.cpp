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
void MooreMachine::setStartState(const QString &name)
{
    start_state = name;
}
void MooreMachine::addInputs(const QString &name)
{
    automate_inputs.append(name);
}
void MooreMachine::addOutputs(const QString &name)
{
    automate_outputs.append(name);
}
void MooreMachine::addVariable(const QString &command)
{
    variables.append(command);
}
const QString &MooreMachine::getName() const
{
    return automate_name;
}

const QString &MooreMachine::getComment() const
{
    return automate_comment;
}
const QString &MooreMachine::getStartState() const
{
    return start_state;
}
void MooreMachine::addState(const QString &name, const std::shared_ptr<MooreState> &state)
{
    states.insert(name, state);
}

void MooreMachine::createAndAddState(std::shared_ptr<MooreState> &state, const QString &stateName, const QString &output)
{
    state = std::make_shared<MooreState>(stateName, output);
    addState(stateName, state);
}
void MooreMachine::createTransition(const std::shared_ptr<MooreState> &state, const QString &action, const QString &targetStateName)
{
    state->addTransition(action, targetStateName);
}

std::shared_ptr<MooreState> MooreMachine::getState(const QString &name)
{
    return states.value(name, nullptr);
}

const QVector<QString> &MooreMachine::getInputs() const
{
    return automate_inputs;
}

const QVector<QString> &MooreMachine::getOutputs() const
{
    return automate_outputs;
}

const QVector<QString> &MooreMachine::getVariables() const
{
    return variables;
}