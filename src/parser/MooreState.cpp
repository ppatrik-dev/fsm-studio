/**
 * @file MooreState.cpp
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Implementation of the MooreState class, which represents a state in a Moore machine
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "MooreState.h"

/**
 * @brief Construct a new Moore State:: Moore State object
 *
 * @param name
 * @param output
 */
MooreState::MooreState(const QString &name, const QString &output)
    : name(name), output(output)
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

void MooreState::setOutput(QString value)
{
    output = value;
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

    /// @brief Removes transitions with the specified target state
    transitions.erase(
        std::remove_if(transitions.begin(), transitions.end(),
                       [&](const MooreTransition &t)
                       {
                           return t.getTarget() == target;
                       }),
        transitions.end());
}
void MooreState::addConditionByTransition(QString conditionText, QString toStateText)
{
    auto transition = findTransitionByTarget(toStateText);
    transition->setInput(conditionText);
}
