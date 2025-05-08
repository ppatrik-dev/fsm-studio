#include "RunExecutionStrategy.h"
#include "MooreMachine.h"
#include "MooreJsClass.h"

RunExecutionStrategy::RunExecutionStrategy(ActionExecutor &actionExecutor,
                                           MooreMachine &mooreMachine,
                                           QObject *parent)
    : QObject(parent),
      actionExecutor(actionExecutor),
      mooreMachine(mooreMachine)
{
}

void RunExecutionStrategy::terminalLog(QString message, MessageType type)
{
    qDebug() << message;
    // emit printLog(message);
}
bool RunExecutionStrategy::step(std::shared_ptr<MooreState> state)
{

    auto result = actionExecutor.evaluate(state->getOutput());
    if (result.toString() == "undefined")
        output = "";
    else
        output = result.toString();
    terminalLog("State: " + state->getName() + " Output: " + output, MessageType::Info);
    for (const auto &transition : state->getTransitions())
    {
        auto boolResult = actionExecutor.evaluate(transition.getInput());
        terminalLog("Condition result: " + QString(boolResult.toBool() ? "true" : "false"), MessageType::TransitionResult);
        if (boolResult.toBool())
        {
            state->unsetCurrent();
            actionExecutor.evaluate("index++;");
            currentState = mooreMachine.getState(transition.getTarget());
            currentState->setCurrent();
            step(currentState);
        }
        else
        {
            return false;
        }
    }

    return true;
}
void RunExecutionStrategy::Execute()
{
    currentState = mooreMachine.getState(mooreMachine.getStartState());
    currentState->setCurrent();

    if (currentState == nullptr)
    {
        terminalLog("Error: Starting state is null!", MessageType::Error);
        return;
    }

    MooreJs *moore = new MooreJs();
    actionExecutor.exposeObject("moore", moore);

    for (const QString &input : mooreMachine.getInputs())
    {
        actionExecutor.evaluate(input);
    }

    for (const QString &output : mooreMachine.getOutputs())
    {
        actionExecutor.evaluate(output);
    }

    for (const QString &variable : mooreMachine.getVariables())
    {
        actionExecutor.evaluate(variable);
    }
    actionExecutor.evaluate("var index = 0;");

    auto result = actionExecutor.evaluate("input");
    terminalLog("Input value: " + result.toString(), MessageType::Info);
    step(currentState);
}
