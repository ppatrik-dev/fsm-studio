#pragma once

#include "IExecutionStrategy.h"
#include "MooreMachine.h"
#include "ActionExecutor.h"

class RunExecutionStrategy : public IExecutionStrategy
{
public:
    void Execute(MooreMachine &machine) override;
    bool step(std::shared_ptr<MooreState> state, ActionExecutor &actionExecute, MooreMachine &machine);
    void terminalLog(QString message, MessageType type);

    enum MessageType
    {
        Error,
        Info,
        TransitionResult,
    };

private:
    QString output;
    // signals:
    //     printLog(QString message);
};
