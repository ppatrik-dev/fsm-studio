#pragma once

#include "IExecutionStrategy.h"
#include "MooreMachine.h"
#include "ActionExecutor.h"
#include <QTimer>
#include <QString>
#include <QObject>

class RunExecutionStrategy : public QObject, public IExecutionStrategy
{
    Q_OBJECT

    enum MessageType
    {
        Error,
        Info,
        TransitionResult,
        Variable,
        Evaluate,
    };

public:
    explicit RunExecutionStrategy(ActionExecutor &actionExecutor,
                                  MooreMachine &mooreMachine,
                                  QObject *parent = nullptr);

    void Execute() override;
    bool step(std::shared_ptr<MooreState> state);
    void terminalLog(QString message, MessageType type);
    void outputVariables();

private:
    QString output;
    std::shared_ptr<MooreState> currentState;
    ActionExecutor &actionExecutor;
    MooreMachine &mooreMachine;

signals:
    void sendMessage(QString type, QString content);
};
