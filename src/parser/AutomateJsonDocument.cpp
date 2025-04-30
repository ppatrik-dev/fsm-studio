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
    machine.setName(jsonObj[" automate_name "].toString());
    machine.setComment(jsonObj["automate_comment"].toString());
    QString start_state = jsonObj["start_state"].toString();
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
