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
    QVector<QString> automate_inputs;
    QVector<QString> automate_outputs;
    QMap<QString, QString> variables;
    QMap<QString, std::shared_ptr<MooreState>> states;

public:
    MooreMachine() = default;
    MooreMachine(const QString &name, const QString &comment);

    void setName(const QString &name);
    void setComment(const QString &comment);

    const QString &getName() const;
    const QString &getComment() const;

    void addState(const QString &name, const std::shared_ptr<MooreState> &state);
    std::shared_ptr<MooreState> getState(const QString &name);
};
