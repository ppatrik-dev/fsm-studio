// ScriptEngine.h
#pragma once
#include <QJSEngine>
#include <QJSValue>
#include <QObject>
#include <QDebug>
#include "MooreJsClass.h"
class ActionExecutor : public QObject
{
    Q_OBJECT

public:
    ActionExecutor(QObject *parent = nullptr);
    QJSValue evaluate(const QString &code);
    void exposeObject(const QString &name, QObject *object);
    QJSEngine &getEngine()
    {
        return engine;
    }
    QString getValue(QString var)
    {
        return engine.globalObject().property(var).toString();
    }
    void setValue(QString var, QString value)
    {
        qDebug() << var << value;
        engine.globalObject().setProperty(var, QJSValue(value));
    }

private:
    QJSEngine engine;
};
