#pragma once

#include <string>
#include <vector>
#include "MooreState.h";
class MooreTransition
{
public:
    std::string input;
    MooreState *target;
    MooreTransition(std::string input, MooreState *target)
        : input(input), target(target) {}
};
