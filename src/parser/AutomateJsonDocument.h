#pragma once

#include <QObject>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QDebug>
#include "MooreMachine.h"

class AutomateJsonDocument : public QObject
{
    Q_OBJECT

public:
    explicit AutomateJsonDocument(QObject *parent = nullptr);
public slots:
    bool loadAutomateFromJsonFile(const QString &fileName, MooreMachine &machine);
    bool saveAutomateToJsonFile(const QString &fileName, MooreMachine &machine);
};
