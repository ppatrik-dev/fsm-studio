#include "StepExecutionStrategy.h"
#include "MooreMachine.h"
#include <QDebug>
#include "MooreJsClass.h"

StepExecutionStrategy::StepExecutionStrategy(ActionExecutor &actionExecutor,
                                             MooreMachine &mooreMachine,
                                             QObject *parent)
    : QObject(parent),
      IExecutionStrategy(),
      m_actionExecutor(actionExecutor),
      m_mooreMachine(mooreMachine)
{
    reset();
}

void StepExecutionStrategy::Execute()
{
    // reset();
    m_finished = false;
    initializeVariables();
    // auto inputResult = m_actionExecutor.evaluate("input");
    // terminalLog("Initial input value: " + inputResult.toString(), Info);
    while (!inputStack.isEmpty() && step())
    {
        qDebug() << "Step succeeded.";
    }
    finalizeExecution();
}

void StepExecutionStrategy::initializeVariables()
{
    QVector<QString> inputs = m_mooreMachine.getInputs();
    for (const QString &input : inputs)
    {

        const QString &varName = m_mooreMachine.extractVariableName(input);
        const QString &varValue = m_mooreMachine.extractVariableValue(input);
        qDebug() << varName << varValue;
        for (int i = varValue.length() - 1; i >= 0; --i)
        {
            QChar ch = varValue[i];
            inputStack.push(m_mooreMachine.createVarCommand(varName, ch));
        }
    }

    // for (const QString &input : m_mooreMachine.getInputs())
    // {

    //     // m_actionExecutor.evaluate(input);
    // }
    for (const QString &output : m_mooreMachine.getOutputs())
    {
        m_actionExecutor.evaluate(output);
    }
    for (const QString &variable : m_mooreMachine.getVariables())
    {
        m_actionExecutor.evaluate(variable);
    }
    m_actionExecutor.evaluate("var index = 0;");
    index = 0;
}

bool StepExecutionStrategy::step()
{
    qDebug() << inputStack.top();
    m_actionExecutor.evaluate(inputStack.top());
    if (m_finished || !m_currentState)
    {
        return false;
    }

    executeStateOutput();

    if (evaluateTransitions())
    {
        inputStack.pop();
        return true;
    }

    return false;
}

void StepExecutionStrategy::executeStateOutput()
{
    auto result = m_actionExecutor.evaluate(m_currentState->getOutput());
    m_output = result.toString() == "undefined" ? "" : result.toString();
    terminalLog("State: " + m_currentState->getName() + " Output: " + m_output, Info);
}

bool StepExecutionStrategy::evaluateTransitions()
{
    for (const auto &transition : m_currentState->getTransitions())
    {
        // terminalLog("Condition: " + transition.getInput(), Info);
        auto boolResult = m_actionExecutor.evaluate(transition.getInput());
        // terminalLog("Condition result: " + QString(boolResult.toBool() ? "true" : "false"), TransitionResult);

        if (boolResult.toBool())
        {
            index++;
            m_currentState->unsetCurrent();
            m_currentState = m_mooreMachine.getState(transition.getTarget());
            m_currentState->setCurrent();
            return true;
        }
    }
    return false;
}

void StepExecutionStrategy::finalizeExecution()
{
    m_finished = true;
    terminalLog("Execution finished in state: " + m_currentState->getName(), Info);
}

void StepExecutionStrategy::reset()
{
    // m_currentState->unsetCurrent();

    m_currentState = m_mooreMachine.getState(m_mooreMachine.getStartState());
    if (!m_currentState)
    {
        terminalLog("Error: Starting state is null!", Error);
        m_finished = true;
    }
    MooreJs *moore = new MooreJs();
    m_actionExecutor.exposeObject("moore", moore);
    m_currentState->setCurrent();
    m_finished = false;
    m_output.clear();

    if (!m_currentState)
    {
        terminalLog("Error: Starting state is null!", Error);
        m_finished = true;
    }
}

void StepExecutionStrategy::terminalLog(QString message, MessageType type)
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
    }
    qDebug().noquote() << prefix << message;
    emit sendMessage(prefix, message);
}