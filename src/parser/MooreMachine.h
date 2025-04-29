#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>
#include "MooreState.h"

class MooreMachine
{
    std::string automate_name;
    std::string automate_comment;
    std::vector<std::string> automate_inputs;
    std::vector<std::string> automate_outputs;
    std::map<std::string, std::string> variables;
    std::map<std::string, std::shared_ptr<MooreState>> states;

public:
    MooreMachine() = default;
    MooreMachine(const std::string &name, const std::string &comment);

    void setName(const std::string &name);
    void setComment(const std::string &comment);

    const std::string &getName() const;
    const std::string &getComment() const;

    void addState(const std::string &name, const std::shared_ptr<MooreState> &state);
    std::shared_ptr<MooreState> getState(const std::string &name);
};
