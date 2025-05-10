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
void RunExecutionStrategy::outputVariables()
{
    for (const QString &input : mooreMachine.getInputs())
    {
        QString var = mooreMachine.extractVariableName(input);
        terminalLog(var + ": " + actionExecutor.getValue(var), MessageType::Variable);
    }

    for (const QString &output : mooreMachine.getOutputs())
    {
        QString var = mooreMachine.extractVariableName(output);
        terminalLog(var + ": " + actionExecutor.getValue(var), MessageType::Variable);
    }

    for (const QString &variable : mooreMachine.getVariables())
    {
        QString var = mooreMachine.extractVariableName(variable);
        terminalLog(var + ": " + actionExecutor.getValue(var), MessageType::Variable);
    }
}
void RunExecutionStrategy::terminalLog(QString message, MessageType type)
{
    QString prefix;
    switch (type)
    {
    case Error:
        prefix = "[ERROR]";
        break;
    case Info:
        prefix = "[INFO]";
        break;
    case TransitionResult:
        prefix = "[TRANSITION]";
        break;
    case Variable:
        prefix = "[VARIABLE]";
        break;
    case Evaluate:
        prefix = "[EVALUATE]";
        break;
    }
    qDebug().noquote() << prefix << message;
    emit sendMessage(prefix, message);
}
bool RunExecutionStrategy::step(std::shared_ptr<MooreState> state)
{
    terminalLog(state->getOutput(), MessageType::Evaluate);
    auto result = actionExecutor.evaluate(state->getOutput());

    if (result.toString() == "undefined")
        output = "";
    else
        output = result.toString();
    terminalLog("State: " + state->getName() + " Output: " + output, MessageType::Info);
    for (const auto &transition : state->getTransitions())
    {
        terminalLog(transition.getInput(), MessageType::Evaluate);
        auto boolResult = actionExecutor.evaluate(transition.getInput());

        terminalLog("Condition result: " + QString(boolResult.toBool() ? "true" : "false"), MessageType::TransitionResult);
        if (boolResult.toBool())
        {
            // state->unsetCurrent();
            terminalLog("index++;", MessageType::Evaluate);
            actionExecutor.evaluate("index++;");

            currentState = mooreMachine.getState(transition.getTarget());
            // currentState->setCurrent();
            outputVariables();
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
    // currentState->setCurrent();

    if (currentState == nullptr)
    {
        terminalLog("Error: Starting state is null!", MessageType::Error);
        return;
    }

    MooreJs *moore = new MooreJs();
    actionExecutor.exposeObject("moore", moore);

    for (const QString &input : mooreMachine.getInputs())
    {
        terminalLog(input, MessageType::Evaluate);
        actionExecutor.evaluate(input);
    }

    for (const QString &output : mooreMachine.getOutputs())
    {
        terminalLog(output, MessageType::Evaluate);
        actionExecutor.evaluate(output);
    }

    for (const QString &variable : mooreMachine.getVariables())
    {
        terminalLog(variable, MessageType::Evaluate);
        actionExecutor.evaluate(variable);
    }
    terminalLog("var index = 0;", MessageType::Evaluate);
    actionExecutor.evaluate("var index = 0;");

    terminalLog("input", MessageType::Evaluate);
    auto result = actionExecutor.evaluate("input");
    terminalLog("Input value: " + result.toString(), MessageType::Info);
    step(currentState);
}
