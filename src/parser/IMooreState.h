#pragma once
#include <QString>

class IMooreState
{
public:
    virtual ~IMooreState() = default;

    virtual QString getName() const = 0;
    virtual QString getOutput() const = 0;
    virtual bool isFinal() const = 0;
    virtual void addTransition(QString &input, QString &target) = 0;
};