#include "AutomateJsonDocument.h"
#include "MooreMachine.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

bool AutomateJsonDocument::loadAutomateFromJsonFile(const QString &fileName, MooreMachine &machine)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Error in opening file !" << fileName;
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull())
    {
        qWarning() << "Failed loading json.";
        return false;
    }

    QJsonObject jsonObj = doc.object();
    machine.setName(jsonObj["automate_name"].toString());
    machine.setStartState(jsonObj["start_state"].toString());
    machine.setComment(jsonObj["automate_comment"].toString());

    QJsonArray inputsArray = jsonObj["inputs"].toArray();

    for (const QJsonValue &value : inputsArray)
    {
        if (value.isString())
        {
            machine.addInputs(value.toString());
        }
    }

    QJsonArray outputsArray = jsonObj["outputs"].toArray();

    for (const QJsonValue &value : outputsArray)
    {
        if (value.isString())
        {
            machine.addOutputs(value.toString());
        }
    }

    QJsonArray variablesArray = jsonObj["variables"].toArray();

    for (const QJsonValue &value : variablesArray)
    {
        if (value.isString())
        {
            machine.addVariable(value.toString());
        }
    }

    QJsonObject statesObj = jsonObj["states"].toObject();

    qDebug() << "States:";
    for (const QString &stateName : statesObj.keys())
    {
        QJsonObject stateDetail = statesObj[stateName].toObject();
        QString output = stateDetail["action"].toString();

        std::shared_ptr<MooreState> state = std::make_shared<MooreState>(stateName, output);
        machine.addState(stateName, state);

        QJsonArray transitionsArray = stateDetail["transitions"].toArray();
        for (const QJsonValue &transitionVal : transitionsArray)
        {
            QJsonObject transitionObj = transitionVal.toObject();

            QString targetStateName = transitionObj["to"].toString();
            QString action = transitionObj["condition"].toString();
            state->addTransition(action, targetStateName);
        }
    }

    return true;
}
bool AutomateJsonDocument::saveAutomateToJsonFile(const QString &fileName, MooreMachine &machine)
{
    QJsonObject jsonObject;
    jsonObject["start_state"] = machine.getStartState();
    jsonObject["automate_comment"] = machine.getComment();
    jsonObject["automate_name"] = machine.getName();

    QJsonArray inputsArray;

    for (const QString &input : machine.getInputs())
    {
        inputsArray.append(input);
    }
    jsonObject["inputs"] = inputsArray;

    QJsonArray outputsArray;
    for (const QString &output : machine.getOutputs())
    {
        outputsArray.append(output);
    }
    jsonObject["outputs"] = outputsArray;

    QJsonArray variablesArray;
    for (const QString &variable : machine.getVariables())
    {
        variablesArray.append(variable);
    }
    jsonObject["variables"] = variablesArray;

    QJsonObject statesObject;

    for (auto it = machine.states.cbegin(); it != machine.states.cend(); ++it)
    {
        const std::shared_ptr<MooreState> &state = it.value();

        QJsonObject stateObj;

        stateObj["action"] = state->getOutput();

        QJsonArray transitionsArray;
        for (const auto &transition : state->transitions)
        {
            QJsonObject transitionObj;
            transitionObj["to"] = transition.target;
            transitionObj["condition"] = transition.input;

            transitionsArray.append(transitionObj);
        }

        stateObj["transitions"] = transitionsArray;
        statesObject[state->getName()] = stateObj;
    }
    jsonObject["states"] = statesObject;
    QJsonDocument jsonDoc(jsonObject);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open file for writing.");
        return false;
    }

    file.write(jsonDoc.toJson());
    file.close();

    qDebug() << "JSON file created successfully!";

    return true;
}
