#pragma once
#include "IMooreState.h"
#include "MooreTransition.h"
#include <QVector>
#include <QString>

class MooreState : public IMooreState
{
    QString name;
    QString output;
    bool is_end_state;

public:
    QVector<MooreTransition> transitions;
    MooreState(const QString &name, const QString &output, bool is_end_state = false);

    QString getName() const override;
    QString getOutput() const override;
    bool isFinal() const override;
    const QVector<MooreTransition> &getTransitions() const;
    void addTransition(const QString &input, const QString &target) override;
};