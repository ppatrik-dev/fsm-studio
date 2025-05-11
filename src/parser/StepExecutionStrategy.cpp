#include "StepExecutionStrategy.h"
#include "MooreMachine.h"
#include <QDebug>
#include "MooreJsClass.h"
#include <QTime>
#include <QApplication>

StepExecutionStrategy::StepExecutionStrategy(ActionExecutor &actionExecutor,
                                             MooreMachine &mooreMachine,
                                             QObject *parent, bool m_isStopped)
    : QObject(parent),
      IExecutionStrategy(),
      m_actionExecutor(actionExecutor),
      m_mooreMachine(mooreMachine),
      m_isStopped(false)
{
    reset();
}
void StepExecutionStrategy::wait(int ms)
{
    QTime end = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < end)
    {
        qApp->processEvents(QEventLoop::AllEvents, 5);
        if (m_isStopped)
        {
            return;
        }
    }
}

bool StepExecutionStrategy::allStacksAreEmpty()
{
    const auto stacks = inputStacks.values();

    for (const QStack<QString> &stack : stacks)
    {
        if (!stack.isEmpty())
        {
            return false;
        }
    }

    return true;
}

void StepExecutionStrategy::Execute()
{
    emit currentStateChanged(m_currentState->getName());
    wait(250);
    m_finished = false;
    initializeVariables();
    bool wasEmptyInitially = allStacksAreEmpty();
    while (step() && (!allStacksAreEmpty() || wasEmptyInitially))
    {
        if (m_isStopped)
        {
            qDebug() << "Execution stopped by user.";
            m_finished = true;
            return;
        }
        qDebug() << "Step succeeded.";
        wait(500);
    }

    finalizeExecution();
}

void StepExecutionStrategy::initializeVariables()
{
    QVector<QString> inputs = m_mooreMachine.getInputs();

    for (const QString &input : inputs)
    {
        QStack<QString> inputStack;
        const QString &varName = m_mooreMachine.extractVariableName(input);
        const QString &varValue = m_mooreMachine.extractVariableValue(input);

        for (int i = varValue.length() - 1; i >= 0; --i)
        {
            QChar ch = varValue[i];
            inputStack.push(m_mooreMachine.createVarCommand(varName, ch));
        }

        inputStacks.insert(varName, inputStack);
    }
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
    if (m_isStopped)
    {
        qDebug() << "Execution stopped by user.";
        return false;
    }
    if (m_finished || !m_currentState)
    {
        return false;
    }

    for (auto it = inputStacks.begin(); it != inputStacks.end(); ++it)
    {
        QStack<QString> &stack = it.value();
        if (!stack.isEmpty())
        {
            terminalLog(stack.top(), Evaluate);
            m_actionExecutor.evaluate(stack.top());
        }
    }

    executeStateOutput();

    if (evaluateTransitions())
    {
        for (auto it = inputStacks.begin(); it != inputStacks.end(); ++it)
        {
            QStack<QString> &stack = it.value();
            if (!stack.isEmpty())
            {
                stack.pop();
            }
        }
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
    if (m_isStopped)
    {
        qDebug() << "Execution stopped by user.";
        m_finished = true;
        return false;
    }
    for (const auto &transition : m_currentState->getTransitions())
    {
        terminalLog("Condition: " + transition.getInput(), Evaluate);
        auto boolResult = m_actionExecutor.evaluate(transition.getInput());
        terminalLog("Condition result: " + QString(boolResult.toBool() ? "true" : "false"), TransitionResult);

        if (boolResult.toBool())
        {
            m_currentState = m_mooreMachine.getState(transition.getTarget());
            emit currentStateChanged(m_currentState->getName());
            outputVariables();
            return true;
        }
    }
    return false;
}

void StepExecutionStrategy::finalizeExecution()
{
    if (m_finished)
    {
        return;
    }
    executeStateOutput();
    m_finished = true;
    terminalLog("Execution finished in state: " + m_currentState->getName(), Info);
    for (auto it = inputStacks.begin(); it != inputStacks.end(); ++it)
    {
        const QString varName = it.key();
        const QStack<QString> inputStack = it.value();

        if (inputStack.isEmpty())
        {
            emit sendRemainingInput(varName, "");
            m_mooreMachine.addGuiInput(varName, "");
            continue;
        }

        QList<QString> tempList = inputStack.toList();
        std::reverse(tempList.begin(), tempList.end());

        qDebug() << "Stack" << varName << "contents:";

        QString remainingInput;

        for (const QString &value : tempList)
        {
            QString variableValue = m_mooreMachine.extractVariableValue(value);
            remainingInput.append(variableValue);
        }
        m_mooreMachine.addGuiInput(varName, remainingInput);
        emit sendRemainingInput(varName, remainingInput);
    }
    for (const QString &output : m_mooreMachine.getOutputs())
    {
        QString var = m_mooreMachine.extractVariableName(output);
        QString varValue = m_actionExecutor.getValue(var);
        m_mooreMachine.addGuiOutput(var, varValue);
        emit sendRemainingOutput(var, varValue);
    }

    for (const QString &variable : m_mooreMachine.getVariables())
    {
        QString var = m_mooreMachine.extractVariableName(variable);
        QString varValue = m_actionExecutor.getValue(var);
        m_mooreMachine.addGuiVariable(var, varValue);
        emit sendRemainingVariable(var, varValue);
    }
}

void StepExecutionStrategy::reset()
{
    if (m_finished)
    {
        return;
    }
    m_currentState = m_mooreMachine.getState(m_mooreMachine.getStartState());
    if (!m_currentState)
    {
        terminalLog("Error: Starting state is null!", Error);
        m_finished = true;
    }
    emit currentStateChanged(m_currentState->getName());
    m_finished = false;
    m_output.clear();
    for (const QString &output : m_mooreMachine.getOutputs())
    {
        QString var = m_mooreMachine.extractVariableName(output);
        m_mooreMachine.addGuiOutput(var, "");
        emit sendRemainingOutput(var, "");
    }
    qDebug() << m_actionExecutor.getValue("output");
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
void StepExecutionStrategy::outputVariables()
{
    for (const QString &input : m_mooreMachine.getInputs())
    {
        QString var = m_mooreMachine.extractVariableName(input);
        terminalLog(var + ": " + m_actionExecutor.getValue(var), Variable);
    }

    for (const QString &output : m_mooreMachine.getOutputs())
    {
        QString var = m_mooreMachine.extractVariableName(output);
        terminalLog(var + ": " + m_actionExecutor.getValue(var), Variable);
    }

    for (const QString &variable : m_mooreMachine.getVariables())
    {
        QString var = m_mooreMachine.extractVariableName(variable);
        terminalLog(var + ": " + m_actionExecutor.getValue(var), Variable);
    }
}
void StepExecutionStrategy::stopEvaluation()
{
    m_isStopped = true;
    terminalLog("Evaluation stopped.", Info);
}
