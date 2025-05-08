#include "RunExecutionStrategy.h"
#include "MooreMachine.h"
#include "MooreJsClass.h"
void RunExecutionStrategy::terminalLog(QString message, MessageType type)
{
    qDebug() << message;
    // emit printLog(message);
}
bool RunExecutionStrategy::step(std::shared_ptr<MooreState> state, ActionExecutor &actionExecute, MooreMachine &machine)
{
    auto result = actionExecute.evaluate(state->getOutput());
    if (result.toString() == "undefined")
        output = "";
    else
        output = result.toString();
    terminalLog("State: " + state->getName() + " Output: " + output, MessageType.Info);
    for (const auto &transition : state->getTransitions())
    {
        auto boolResult = actionExecute.evaluate(transition.getInput());
        terminalLog("Condition result: " + QString(boolResult.toBool() ? "true" : "false"), MessageType.TransitionResult);
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
    if (state == nullptr)
    {
        terminalLog("Error: Starting state is null!", MessageType.Error);
        return;
    }
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
