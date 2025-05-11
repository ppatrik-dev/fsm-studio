/**
 * @file AutomateJsonDocument.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
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
 * @brief
 *
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
     * @brief
     *
     * @param fileName
     * @param machine
     * @return true
     * @return false
     */
    bool loadAutomateFromJsonFile(const QString &fileName, MooreMachine &machine);
    /**
     * @brief
     *
     * @param fileName
     * @param machine
     * @return true
     * @return false
     */
    bool saveAutomateToJsonFile(const QString &fileName, MooreMachine &machine);
};
