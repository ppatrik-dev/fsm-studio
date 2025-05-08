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
QVector<MooreTransition> &MooreState::getTransitions()
{
    return transitions;
}
MooreTransition *MooreState::findTransitionByTarget(QString &target)
{
    for (MooreTransition &t : getTransitions())
    {
        if (t.getTarget() == target)
        {
            return &t;
        }
    }
    return nullptr;
}
void MooreState::deleteTransitionByTarget(const QString &target)
{
    auto &transitions = getTransitions();

    transitions.erase(
        std::remove_if(transitions.begin(), transitions.end(),
                       [&](const MooreTransition &t)
                       {
                           return t.getTarget() == target;
                       }),
        transitions.end());
}
