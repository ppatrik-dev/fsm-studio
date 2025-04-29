#pragma once
#include "IMooreState.h"
#include <memory>
#include <unordered_map>

class StateFactory
{
    std::unordered_map<std::string, std::unique_ptr<IMooreState>> states;

public:
    IMooreState *createState(const std::string &name, const std::string &output);
    IMooreState *getState(const std::string &name) const;
};