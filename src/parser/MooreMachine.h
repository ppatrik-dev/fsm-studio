#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <memory>
#include "MooreState.h"

class MooreMachine
{
    QString automate_name;
    QString automate_comment;
    QString start_state;
    QVector<QString> automate_inputs;
    QVector<QString> automate_outputs;
    QMap<QString, QString> variables;

public:
    QMap<QString, std::shared_ptr<MooreState>> states;
    MooreMachine() = default;
    MooreMachine(const QString &name, const QString &comment);

    void setName(const QString &name);
    void setComment(const QString &comment);
    void setStartState(const QString &name);
    void addInputs(const QString &name);
    void addOutputs(const QString &name);

    const QString &getName() const;
    const QString &getComment() const;
    const QString &getStartState() const;
    const QVector<QString> &getInputs() const;
    const QVector<QString> &getOutputs() const;

    void addState(const QString &name, const std::shared_ptr<MooreState> &state);
    std::shared_ptr<MooreState> getState(const QString &name);
};
