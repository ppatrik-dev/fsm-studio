#include "MooreStateFactory.h"
#include "MooreState.h"

IMooreState *StateFactory::createState(const std::string &name, const std::string &output)
{
    auto state = std::make_unique<MooreState>(name, output);
    IMooreState *rawPtr = state.get();
    states[name] = std::move(state);
    return rawPtr;
}

IMooreState *StateFactory::getState(const std::string &name) const
{
    auto it = states.find(name);
    return it != states.end() ? it->second.get() : nullptr;
}