#include "MooreMachine.h"
#include <QDebug>
MooreMachine::MooreMachine(QObject *parent)
    : QObject(parent) {}

MooreMachine::MooreMachine(const QString &name, const QString &comment, QObject *parent)
    : QObject(parent), automate_name(name), automate_comment(comment) {}

MooreMachine::~MooreMachine()
{
    states.clear();
}
QString MooreMachine::extractVariableName(const QString &command)
{
    QRegularExpression regex(R"(\bvar\s+(\w+))");
    QRegularExpressionMatch match = regex.match(command);

    if (match.hasMatch())
    {
        return match.captured(1);
    }
    return {};
}
QString MooreMachine::extractVariableValue(const QString &command)
{
    QRegularExpression regex(R"(\bvar\s+\w+\s*=\s*(.+?))\s*;?\s*$)");
    QRegularExpressionMatch match = regex.match(command);

    if (match.hasMatch())
    {
        return match.captured(1).trimmed();
    }
    return {};
}

QString MooreMachine::createVarCommand(const QString &name, const QString &value)
{
    return QString("var %1 = '%2';").arg(name, value);
}
void MooreMachine::setName(const QString &name)
{
    automate_name = name;
}

void MooreMachine::setComment(const QString &comment)
{
    automate_comment = comment;
}
void MooreMachine::setStartState(const QString &name)
{
    start_state = name;
}
void MooreMachine::addInputs(const QString &name)
{
    QString key = extractVariableName(name);
    automate_inputs.insert(key, name);
}
void MooreMachine::addOutputs(const QString &name)
{
    QString key = extractVariableName(name);
    automate_outputs.insert(key, name);
}
void MooreMachine::addVariable(const QString &command)
{
    QString key = extractVariableName(command);
    variables.insert(key, command);
}
const QString &MooreMachine::getName() const
{
    return automate_name;
}

const QString &MooreMachine::getComment() const
{
    return automate_comment;
}
const QString &MooreMachine::getStartState() const
{
    return start_state;
}
void MooreMachine::addState(const QString &name, const std::shared_ptr<MooreState> &state)
{
    states.insert(name, state);
}

void MooreMachine::createAndAddState(std::shared_ptr<MooreState> &state, const QString &stateName, const QString &output)
{
    state = std::make_shared<MooreState>(stateName, output);
    addState(stateName, state);
}
void MooreMachine::createTransition(const std::shared_ptr<MooreState> &state, const QString &action, const QString &targetStateName)
{
    state->addTransition(action, targetStateName);
}

std::shared_ptr<MooreState> MooreMachine::getState(const QString &name)
{
    return states.value(name, nullptr);
}

QVector<QString> MooreMachine::getInputs() const
{
    return QVector<QString>::fromList(automate_inputs.values());
}

QVector<QString> MooreMachine::getOutputs() const
{
    return QVector<QString>::fromList(automate_outputs.values());
}

QVector<QString> MooreMachine::getVariables() const
{
    return QVector<QString>::fromList(variables.values());
}
void MooreMachine::getGuiMap(QMap<QString, QString> &automate_backup, const QString &mode)
{
    ;
    if (mode == "input")
    {
        automate_backup = automate_inputs;
    }
    else if (mode == "output")
    {
        automate_backup = automate_outputs;
    }
    else if (mode == "variable")
    {
        automate_backup = variables;
    }
    else
    {
        automate_backup = QMap<QString, QString>();
    }

    for (auto it = automate_backup.begin(); it != automate_backup.end(); ++it)
    {
        QString backupValue = it.value();
        it.value() = extractVariableValue(backupValue);
    }
}

void MooreMachine::addGuiInput(const QString &name, const QString &value)
{
    automate_inputs.insert(name, createVarCommand(name, value));
}
void MooreMachine::deleteGuiInput(const QString &name)
{
    if (automate_inputs.contains(name))
    {
        automate_inputs.remove(name);
    }
}
void MooreMachine::addGuiOutput(const QString &name, const QString &value)
{
    automate_outputs.insert(name, createVarCommand(name, value));
}
void MooreMachine::deleteGuiOutput(const QString &name)
{
    if (automate_outputs.contains(name))
    {
        automate_outputs.remove(name);
    }
}
void MooreMachine::addGuiVariable(const QString &name, const QString &value)
{
    variables.insert(name, createVarCommand(name, value));
}
void MooreMachine::deleteGuiVariable(const QString &name)
{
    if (variables.contains(name))
    {
        variables.remove(name);
    }
}
void MooreMachine::getGuiName(QString &name)
{
    name = automate_name;
}
void MooreMachine::getGuiComment(QString &comment)
{
    comment = automate_comment;
}
void MooreMachine::getGuiStartState(QString &startState)
{
    startState = start_state;
}
void MooreMachine::clearMachine()
{
    states.clear();
}