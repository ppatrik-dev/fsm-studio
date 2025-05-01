#include "MooreAutomateSimulator.h"
#include "MooreState.h"
#include "ActionExecutor.h"

MooreSimulator::MooreSimulator(MooreMachine *machine)
    : machine(machine), currentState(nullptr)
{
}
bool MooreSimulator::step(std::shared_ptr<MooreState> state, ActionExecutor &engine)
{
    auto result = engine.evaluate(state->getOutput());
    qDebug() << "State: " << state->getName() << "Output: " << result.toInt();
    for (const auto &transition : state->getTransitions())
    {
        auto boolResult = engine.evaluate(transition.getInput());
        qDebug() << "Condition result:" << boolResult.toBool();
        if (boolResult.toBool())
        {

            // step(machine->getState(transition.getTarget()));
            return true;
        }
    }

    return true;
}
bool MooreSimulator::run()
{
    std::shared_ptr<MooreState> state = machine->getState(machine->getStartState());
    ActionExecutor engine;

    for (const QString &input : machine->getInputs())
    {
        engine.evaluate(input);
    }

    for (const QString &output : machine->getOutputs())
    {
        engine.evaluate(output);
    }

    for (const QString &variable : machine->getVariables())
    {
        engine.evaluate(variable);
    }

    auto result = engine.evaluate(state->getOutput());
    qDebug() << "State: " << state->getName() << "Output: " << result.toInt();

    for (const auto &transition : state->getTransitions())
    {
        auto boolResult = engine.evaluate(transition.getInput());
        qDebug() << "Condition Result:" << boolResult.toBool();
        if (boolResult.toBool())
        {

            step(machine->getState(transition.getTarget()), engine);
            return true;
        }
    }
    return true;
}