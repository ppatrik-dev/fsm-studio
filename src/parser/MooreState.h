#pragma once
#include "IMooreState.h"
#include "MooreTransition.h"
#include <QVector>
#include <QString>

class MooreState : public IMooreState
{
    QString name;
    QString output;
    bool current_state;

public:
    QVector<MooreTransition> transitions;
    MooreState(const QString &name, const QString &output, bool current_state = false);

    QString getName() const override;
    QString getOutput() const override;
    void setOutput(QString value);
    bool isCurrent() const;
    void setCurrent();
    void unsetCurrent();
    QVector<MooreTransition> &getTransitions();
    void addConditionByTransition(QString conditionText, QString toStateText);
    MooreTransition *findTransitionByTarget(QString &target);
    void addTransition(const QString &input, const QString &target) override;
    void deleteTransitionByTarget(const QString &target);
};
