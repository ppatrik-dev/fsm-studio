/**
 * @file ActionExecutor.cpp
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "ActionExecutor.h"

/**
 * @brief Construct a new Action Executor:: Action Executor object
 *
 * @param parent
 */
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
