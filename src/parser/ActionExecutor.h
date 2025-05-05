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

private:
    QJSEngine engine;
};
