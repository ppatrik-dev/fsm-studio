#pragma once

#include "IExecutionStrategy.h"
#include "MooreMachine.h"
#include "ActionExecutor.h"
#include <QTimer>
#include <QObject>

class RunExecutionStrategy : public QObject, public IExecutionStrategy
{
    Q_OBJECT

    enum MessageType
    {
        Error,
        Info,
        TransitionResult,
    };

public:
    RunExecutionStrategy(ActionExecutor &actionExecutor, MooreMachine &mooreMachine, QObject *parent = nullptr)
        : QObject(parent), actionExecutor(actionExecutor), mooreMachine(mooreMachine)
    {
    }

    void Execute(MooreMachine &mooreMachine) override;
    bool step(std::shared_ptr<MooreState> state, ActionExecutor &actionExecute, MooreMachine &mooreMachine);
    void terminalLog(QString message, MessageType type);

private:
    QString output;
    std::shared_ptr<MooreState> currentState;
    ActionExecutor &actionExecutor;
    MooreMachine &mooreMachine;

public slots:
    void
    stepTimeout(qint32 timeout);
};
