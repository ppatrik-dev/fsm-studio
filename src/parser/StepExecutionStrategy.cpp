/**
 * @file StepExecutionStrategy.cpp
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Implementation of the StepExecutionStrategy class for stepwise Moore machine execution
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "StepExecutionStrategy.h"

/**
 * @brief Implementation of the delay
 *
 * @param ms
 */
void wait(int ms)
{
    QTime end = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < end)
    {
        qApp->processEvents(QEventLoop::AllEvents, 5);
    }
}
/**
 * @brief Construct a new Step Execution Strategy:: Step Execution Strategy object
 *
 * @param actionExecutor
 * @param mooreMachine
 * @param parent
 */
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
    /// @brief Check if there is any input and if there are transitions available

    while (step() && (!allStacksAreEmpty() || wasEmptyInitially))
    {
        terminalLog("Step succeeded.", Info);
        wait(500);
    }

    finalizeExecution();
    emit endOfSimulation();
}

void StepExecutionStrategy::initializeVariables()
{
    QVector<QString> inputs = m_mooreMachine.getInputs();

    for (const QString &input : inputs)
    {
        QStack<QString> inputStack;
        const QString &varName = m_mooreMachine.extractVariableName(input);
        const QString &varValue = m_mooreMachine.extractVariableValue(input);
        /// @brief Reverse because I adding to Stack
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
}

bool StepExecutionStrategy::step()
{
    for (auto it = inputStacks.begin(); it != inputStacks.end(); ++it)
    {
        QStack<QString> &stack = it.value();
        if (!stack.isEmpty())
        {
            terminalLog(stack.top(), Evaluate);
            m_actionExecutor.evaluate(stack.top());
        }
    }
    if (m_finished || !m_currentState)
    {
        return false;
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
    for (const auto &transition : m_currentState->getTransitions())
    {
        terminalLog("Condition: " + transition.getInput(), Evaluate);
        /// @brief Checking condition
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
    executeStateOutput();
    m_finished = true;
    terminalLog("Execution finished in state: " + m_currentState->getName(), Info);
    /// @brief Send remaining input characters to GUI
    for (auto it = inputStacks.begin(); it != inputStacks.end(); ++it)
    {
        const QString varName = it.key();
        const QStack<QString> inputStack = it.value();

        if (inputStack.isEmpty())
        {
            m_mooreMachine.addGuiInput(varName, "");
            emit sendRemainingInput(varName, "");
            continue;
        }
        /// @brief Reverse string because I use Stack
        QList<QString> tempList = inputStack.toList();
        std::reverse(tempList.begin(), tempList.end());

        QString remainingInput;

        for (const QString &value : tempList)
        {
            QString variableValue = m_mooreMachine.extractVariableValue(value);
            remainingInput.append(variableValue);
        }
        // Update inputs in intern context
        m_mooreMachine.addGuiInput(varName, remainingInput);
        emit sendRemainingInput(varName, remainingInput);
    }
    /// @brief Send final output and variable states to GUI
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
        /// @brief Reset outputs in intern context and GUI outputs
        m_mooreMachine.addGuiOutput(var, "");
        emit sendRemainingOutput(var, "");
    }
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