/**
 * @file ActionExecutor.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <QJSEngine>
#include <QJSValue>
#include <QObject>
#include <QDebug>
#include "MooreJsClass.h"
/**
 * @brief
 *
 */
class ActionExecutor : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Action Executor object
     *
     * @param parent
     */
    ActionExecutor(QObject *parent = nullptr);
    /**
     * @brief Evaluate command in JS
     *
     * @param code
     * @return QJSValue
     */
    QJSValue evaluate(const QString &code);
    /**
     * @brief add custom object to QJSEngine
     *
     * @param name
     * @param object
     */
    void exposeObject(const QString &name, QObject *object);
    /**
     * @brief Get the Engine object
     *
     * @return QJSEngine&
     */
    QJSEngine &getEngine()
    {
        return engine;
    }
    /**
     * @brief Get the Value object
     *
     * @param var
     * @return QString
     */
    QString getValue(QString var)
    {
        return engine.globalObject().property(var).toString();
    }
    /**
     * @brief Set the Value object
     *
     * @param var
     * @param value
     */
    void setValue(QString var, QString value)
    {
        engine.globalObject().setProperty(var, QJSValue(value));
    }

private:
    QJSEngine engine;
};
