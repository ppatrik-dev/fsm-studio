#include "RunExecutionStrategy.h"
#include "MooreMachine.h"
#include "MooreJsClass.h"
RunExecutionStrategy::RunExecutionStrategy(QObject *parent)
    : QObject(parent)
{
}

void RunExecutionStrategy::terminalLog(QString message, MessageType type)
{
    qDebug() << message;
    // emit printLog(message);
}
bool RunExecutionStrategy::step(std::shared_ptr<MooreState> state, ActionExecutor &actionExecute, MooreMachine &mooreMachine)
{
    auto result = actionExecute.evaluate(state->getOutput());
    if (result.toString() == "undefined")
        output = "";
    else
        output = result.toString();
    terminalLog("State: " + state->getName() + " Output: " + output, MessageType::Info);
    for (const auto &transition : state->getTransitions())
    {
        auto boolResult = actionExecute.evaluate(transition.getInput());
        terminalLog("Condition result: " + QString(boolResult.toBool() ? "true" : "false"), MessageType::TransitionResult);
        if (boolResult.toBool())
        {
            actionExecute.evaluate("index++;");
            currentState = mooreMachine.getState(transition.getTarget());
            step(currentState, actionExecute, mooreMachine);
        }
        else
        {
            return false;
        }
    }

    return true;
}
void RunExecutionStrategy::stepTimeout(qint32 timeout)
{
    QTimer::singleShot(timeout, this, [=]()
                       { step(currentState, actionExecutor, mooreMachine); });
}
void RunExecutionStrategy::Execute()
{
    currentState = mooreMachine.getState(mooreMachine.getStartState());

    if (currentState == nullptr)
    {
        terminalLog("Error: Starting state is null!", MessageType::Error);
        return;
    }

    MooreJs *moore = new MooreJs();
    actionExecute.exposeObject("moore", moore);
    connect(moore, &MooreJs::stepTimeout, this, &RunExecutionStrategy::stepTimeout);

    for (const QString &input : mooreMachine.getInputs())
    {
        actionExecute.evaluate(input);
    }

    for (const QString &output : mooreMachine.getOutputs())
    {
        actionExecute.evaluate(output);
    }

    for (const QString &variable : mooreMachine.getVariables())
    {
        actionExecute.evaluate(variable);
    }
    actionExecute.evaluate("var index = 0;");

    auto result = actionExecute.evaluate("input");
    terminalLog("Input value: " + result.toString(), MessageType::Info);
    step(currentState, actionExecute, mooreMachine);
}
