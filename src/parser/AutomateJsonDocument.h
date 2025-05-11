/**
 * @file AutomateJsonDocument.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Provides serialization and deserialization of a Moore machine to and from JSON format
 * @version 0.3
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
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

/**
 * @class AutomateJsonDocument
 * @brief Provides serialization and deserialization of a Moore machine to and from JSON format.
 */
class AutomateJsonDocument : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Automate Json Document object
     *
     * @param parent
     */
    explicit AutomateJsonDocument(QObject *parent = nullptr);
public slots:
    /**
     * @brief Load a JSON file and create a machine object from it.
     *
     * @param fileName
     * @param machine
     * @return true
     * @return false
     */
    bool loadAutomateFromJsonFile(const QString &fileName, MooreMachine &machine);
    /**
     * @brief Save to JSON file machine object
     *
     * @param fileName
     * @param machine
     * @return true
     * @return false
     */
    bool saveAutomateToJsonFile(const QString &fileName, MooreMachine &machine);
};
