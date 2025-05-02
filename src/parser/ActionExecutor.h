// ScriptEngine.h
#pragma once
#include <QJSEngine>
#include <QJSValue>
#include <QObject>
#include <QDebug>

class ActionExecutor : public QObject
{
    Q_OBJECT

public:
    QJSValue evaluate(const QString &code);

private:
    QJSEngine engine;
};
