#pragma once

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QDebug>
#include "MooreMachine.h"
class AutomateJsonDocument
{
public:
    bool loadAutomateFromJsonFile(const QString &fileName, MooreMachine &machine);
    bool saveAutomateToJsonFile(const QString &fileName, MooreMachine &machine);
};
