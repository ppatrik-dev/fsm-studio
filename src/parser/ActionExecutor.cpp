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
    return result;
}

void ActionExecutor::exposeObject(const QString &name, QObject *object)
{
    QJSValue objValue = engine.newQObject(object);
    engine.globalObject().setProperty(name, objValue);
}
