#include "ActionExecutor.h"

ActionExecutor::ActionExecutor(QObject *parent)
    : QObject(parent)
{
}

QJSValue ActionExecutor::evaluate(const QString &code)
{

    QJSValue result = engine.evaluate(code);
    if (result.isError())
    {
        qWarning() << "Uncaught exception at line"
                   << result.property("lineNumber").toInt()
                   << ":" << result.toString();
    }
    qDebug() << "Som tu" << result.toString();
    return result;
}

void ActionExecutor::exposeObject(const QString &name, QObject *object)
{
    if (!object)
    {
        qWarning() << "Attempted to expose a null object";
        return;
    }
    QJSValue objValue = engine.newQObject(object);
    engine.globalObject().setProperty(name, objValue);
}
