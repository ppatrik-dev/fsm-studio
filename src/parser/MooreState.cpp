#include "MooreState.h"

MooreState::MooreState(const QString &name, const QString &output, bool current_state)
    : name(name), output(output), current_state(current_state)
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

bool MooreState::isCurrent() const
{
    return current_state;
}
void MooreState::setCurrent()
{
    current_state = true;
}
void MooreState::unsetCurrent()
{
    current_state = false;
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
