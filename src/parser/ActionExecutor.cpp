#include "ActionExecutor.h"

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
