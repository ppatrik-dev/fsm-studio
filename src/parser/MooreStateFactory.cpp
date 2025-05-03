#include "MooreStateFactory.h"
#include "MooreState.h"

std::shared_ptr<IMooreState> StateFactory::createState(const QString &name, const QString &output)
{
    auto state = std::make_shared<MooreState>(name, output);
    states.insert(name, state);
    return state;
}

std::shared_ptr<IMooreState> StateFactory::getState(const QString &name) const
{
    return states.value(name, nullptr);
}
