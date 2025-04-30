#pragma once
#include <QString>

class MooreTransition
{
public:
    QString input;
    QString target;

    MooreTransition(QString &input, QString &target)
        : input(input), target(target) {}
};