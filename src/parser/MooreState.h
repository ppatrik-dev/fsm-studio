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
    QVector<MooreTransition> transitions;

public:
    MooreState(const QString &name, const QString &output, bool is_end_state = false);

    QString getName() const override;
    QString getOutput() const override;
    bool isFinal() const override;
    void addTransition(QString &input, QString &target) override;
};