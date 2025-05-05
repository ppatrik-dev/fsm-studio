#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QObject>
#include <memory>
#include "MooreState.h"

class MooreMachine : public QObject
{
    Q_OBJECT

    QString automate_name;
    QString automate_comment;
    QString start_state;
    QVector<QString> automate_inputs;
    QVector<QString> automate_outputs;
    QVector<QString> variables;

public:
    QMap<QString, std::shared_ptr<MooreState>> states;
    explicit MooreMachine(QObject *parent = nullptr);
    MooreMachine(const QString &name, const QString &comment, QObject *parent = nullptr);

    ~MooreMachine() override;

    void addInputs(const QString &name);
    void addOutputs(const QString &name);
    void addVariable(const QString &command);

    const QString &getName() const;
    const QString &getComment() const;
    const QString &getStartState() const;
    const QVector<QString> &getInputs() const;
    const QVector<QString> &getOutputs() const;
    const QVector<QString> &getVariables() const;

    void addState(const QString &name, const std::shared_ptr<MooreState> &state);
    std::shared_ptr<MooreState> getState(const QString &name);
public slots:
    void createAndAddState(std::shared_ptr<MooreState> &state, const QString &stateName, const QString &output);
    void createTransition(const std::shared_ptr<MooreState> &state, const QString &action, const QString &targetStateName);
    void setName(const QString &name);
    void setComment(const QString &comment);
    void setStartState(const QString &name);
    // void addGuiInput();
    // void addGuiOutput();
    // void addGuiVariable();
};
