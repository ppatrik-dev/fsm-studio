#include "RunExecutionStrategy.h"
#include "MooreMachine.h"

bool RunExecutionStrategy::step(std::shared_ptr<MooreState> state, ActionExecutor &engine, MooreMachine &machine)
{
    auto result = engine.evaluate(state->getOutput());
    if (result.toString() == "undefined")
        output += "";
    else
        output += result.toString();
    qDebug()
        << "State:" << state->getName() << "Output:" << output;
    for (const auto &transition : state->getTransitions())
    {
        auto boolResult = engine.evaluate(transition.getInput());
        qDebug() << "Condition result:" << boolResult.toBool();
        if (boolResult.toBool())
        {
            engine.evaluate("index++;");
            step(machine.getState(transition.getTarget()), engine, machine);
        }
        else
        {
            return false;
        }
    }

    return true;
}
void RunExecutionStrategy::Execute(MooreMachine &machine)
{
    std::shared_ptr<MooreState> state = machine.getState(machine.getStartState());
    ActionExecutor engine;

    for (const QString &input : machine.getInputs())
    {
        engine.evaluate(input);
    }

    for (const QString &output : machine.getOutputs())
    {
        engine.evaluate(output);
    }

    for (const QString &variable : machine.getVariables())
    {
        engine.evaluate(variable);
    }
    engine.evaluate("var index = 0;");
    auto result = engine.evaluate("input");
    qDebug() << "Input value: " << result.toString();
    step(state, engine, machine);
}
