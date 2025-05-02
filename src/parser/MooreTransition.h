#pragma once
#include <QString>

class MooreTransition
{
public:
    MooreTransition(const QString &input, const QString &target)
        : input(input), target(target) {}

    QString getInput() const { return input; }
    QString getTarget() const { return target; }

private:
    QString input;
    QString target;
};
