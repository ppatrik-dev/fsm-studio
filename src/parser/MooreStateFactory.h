/**
 * @file MooreStateFactory.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Header file for the StateFactory class, which manages the creation and retrieval of MooreState objects
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "IMooreState.h"
#include <memory>
#include <QMap>
#include <QString>
/**
 * @class StateFactory
 * @brief A factory class that manages the creation and retrieval of MooreState objects
 */
class StateFactory
{
    QMap<QString, std::shared_ptr<IMooreState>> states;

public:
    /**
     * @brief Create a State object
     *
     * @param name of the state
     * @param output output of the state
     * @return std::shared_ptr<IMooreState>
     */
    std::shared_ptr<IMooreState> createState(const QString &name, const QString &output);
    /**
     * @brief Get the State object
     *
     * @param name of the state
     * @return std::shared_ptr<IMooreState>
     */
    std::shared_ptr<IMooreState> getState(const QString &name) const;
};
