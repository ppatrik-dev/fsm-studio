/**
 * @file MooreStateFactory.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
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
 * @brief
 *
 */
class StateFactory
{
    /// @brief
    QMap<QString, std::shared_ptr<IMooreState>> states;

public:
    /**
     * @brief Create a State object
     *
     * @param name
     * @param output
     * @return std::shared_ptr<IMooreState>
     */
    std::shared_ptr<IMooreState> createState(const QString &name, const QString &output);
    /**
     * @brief Get the State object
     *
     * @param name
     * @return std::shared_ptr<IMooreState>
     */
    std::shared_ptr<IMooreState> getState(const QString &name) const;
};
