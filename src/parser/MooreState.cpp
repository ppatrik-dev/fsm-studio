#include "MooreState.h"

MooreState::MooreState(const QString &name, const QString &output, bool is_end_state)
    : name(name), output(output), is_end_state(is_end_state)
{
}

QString MooreState::getName() const
{
    return name;
}

QString MooreState::getOutput() const
{
    return output;
}

bool MooreState::isFinal() const
{
    return is_end_state;
}

void MooreState::addTransition(const QString &input, const QString &targetName)
{
    transitions.append(MooreTransition(input, targetName));
}
const QVector<MooreTransition> &MooreState::getTransitions() const
{
    return transitions;
}