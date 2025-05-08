#pragma once

#include <QObject>
#include "IExecutionStrategy.h"

class MachineExecutor : public QObject
{
Q_OBJECT // This must be here!

    public : explicit MachineExecutor(MooreMachine *machine, QObject *parent = nullptr);

public slots:
    void SetStrategy(IExecutionStrategy *strategy);
    void Execute();

private:
    IExecutionStrategy *strategy_ = nullptr;
    MooreMachine *machine;
    MooreState *currentState;
    QString output;
};
