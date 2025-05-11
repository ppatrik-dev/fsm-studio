#pragma once

#include "IExecutionStrategy.h"
#include "MooreMachine.h"
#include "ActionExecutor.h"
#include <QObject>
#include <memory>
#include <QCoreApplication>
#include <QStack>
#include <algorithm>
#include <atomic>

class StepExecutionStrategy : public QObject, public IExecutionStrategy
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
    explicit StepExecutionStrategy(ActionExecutor &actionExecutor,
                                   MooreMachine &mooreMachine,
                                   QObject *parent = nullptr, bool m_isStopped = false);
    void Execute() override;

    void terminalLog(QString message, MessageType type);
    void initializeVariables();
    void executeStateOutput();
    bool evaluateTransitions();
    void finalizeExecution();
    bool isFinished() const { return m_finished; }
    bool allStacksAreEmpty();
    void outputVariables();
    void wait(int ms);

private:
    QString m_output;
    std::atomic<bool> m_finished = false;
    std::shared_ptr<MooreState> m_currentState;
    ActionExecutor &m_actionExecutor;
    MooreMachine &m_mooreMachine;
    QVector<QString> m_input;
    qint32 index;
    QMap<QString, QStack<QString>> inputStacks;
    bool m_isStopped;
public slots:
    bool step();
    void reset();
    void stopEvaluation();
signals:
    void sendMessage(QString type, QString content);
    void currentStateChanged(QString name);
    void sendRemainingInput(QString varName, QString remainingInput);
    void sendRemainingOutput(QString varName, QString remainingInput);
    void sendRemainingVariable(QString varName, QString remainingInput);
};