#pragma once

#include "IMooreState.h"
#include <memory>
#include <QMap>
#include <QString>

class StateFactory
{
    QMap<QString, std::shared_ptr<IMooreState>> states;

public:
    std::shared_ptr<IMooreState> createState(const QString &name, const QString &output);
    std::shared_ptr<IMooreState> getState(const QString &name) const;
};
