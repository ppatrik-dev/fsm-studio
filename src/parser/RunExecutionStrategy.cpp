#include "RunExecutionStrategy.h"
#include "MooreMachine.h"
#include "MooreJsClass.h"

bool RunExecutionStrategy::step(std::shared_ptr<MooreState> state, ActionExecutor &actionExecute, MooreMachine &machine)
{
    auto result = actionExecute.evaluate(state->getOutput());
    if (result.toString() == "undefined")
        output += "";
    else
        output += result.toString();
    qDebug()
        << "State:" << state->getName() << "Output:" << output;
    for (const auto &transition : state->getTransitions())
    {
        auto boolResult = actionExecute.evaluate(transition.getInput());
        qDebug() << "Condition result:" << boolResult.toBool();
        if (boolResult.toBool())
        {
            actionExecute.evaluate("index++;");
            step(machine.getState(transition.getTarget()), actionExecute, machine);
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
    ActionExecutor actionExecute;

    MooreJs *moore = new MooreJs();
    actionExecute.exposeObject("moore", moore);

    for (const QString &input : machine.getInputs())
    {
        actionExecute.evaluate(input);
    }

    for (const QString &output : machine.getOutputs())
    {
        actionExecute.evaluate(output);
    }

    for (const QString &variable : machine.getVariables())
    {
        actionExecute.evaluate(variable);
    }
    actionExecute.evaluate("var index = 0;");

    auto result = actionExecute.evaluate("input");

    qDebug() << "Input value: " << result.toString();
    step(state, actionExecute, machine);
}
