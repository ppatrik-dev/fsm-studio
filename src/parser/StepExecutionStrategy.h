#pragma once

#include "IExecutionStrategy.h"
#include "MooreMachine.h"
#include "ActionExecutor.h"
#include <QObject>
#include <memory>

class StepExecutionStrategy : public QObject, public IExecutionStrategy
{
    Q_OBJECT

    enum MessageType
    {
        Error,
        Info,
        TransitionResult,
    };

public:
    explicit StepExecutionStrategy(ActionExecutor &actionExecutor,
                                   MooreMachine &mooreMachine,
                                   QObject *parent = nullptr);

    void Execute() override;
    bool step();
    void reset();
    void terminalLog(QString message, MessageType type);
    void initializeVariables();
    void executeStateOutput();
    bool evaluateTransitions();
    void finalizeExecution();
    bool isFinished() const { return m_finished; }

private:
    QString m_output;
    bool m_finished = false;
    std::shared_ptr<MooreState> m_currentState;
    ActionExecutor &m_actionExecutor;
    MooreMachine &m_mooreMachine;

signals:
    void sendMessage(QString type, QString content);
};