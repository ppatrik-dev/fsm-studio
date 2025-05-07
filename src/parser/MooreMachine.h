#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QObject>
#include <memory>
#include "MooreState.h"
#include <QRegularExpression>

class MooreMachine : public QObject
{
    Q_OBJECT

    QString automate_name;
    QString automate_comment;
    QString start_state;
    QMap<QString, QString> automate_inputs;
    QMap<QString, QString> automate_outputs;
    QMap<QString, QString> variables;

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
    QVector<QString> getInputs() const;
    QVector<QString> getOutputs() const;
    QVector<QString> getVariables() const;
    QString createVarCommand(const QString &name, const QString &value);
    QString extractVariableName(const QString &command);
    QString extractVariableValue(const QString &command);
    void addState(const QString &name, const std::shared_ptr<MooreState> &state);
    std::shared_ptr<MooreState> getState(const QString &name);

public slots:
    void createAndAddState(std::shared_ptr<MooreState> &state, const QString &stateName, const QString &output);
    void createTransition(const std::shared_ptr<MooreState> &state, const QString &action, const QString &targetStateName);
    void setName(const QString &name);
    void setComment(const QString &comment);
    void setStartState(const QString &name);
    void addGuiInput(const QString &name, const QString &value);
    void deleteGuiInput(const QString &name);
    void addGuiOutput(const QString &name, const QString &value);
    void deleteGuiOutput(const QString &name);
    void addGuiVariable(const QString &name, const QString &value);
    void deleteGuiVariable(const QString &name);
    void getGuiMap(QMap<QString, QString> &automate_backup, const QString &mode);
    void getGuiName(QString &name);
    void getGuiComment(QString &comment);
    void getGuiStartState(QString &startState);
};
