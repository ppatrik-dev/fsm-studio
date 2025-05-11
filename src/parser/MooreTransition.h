/**
 * @file MooreTransition.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <QString>
/**
 * @brief
 *
 */
class MooreTransition
{
public:
    /**
     * @brief Construct a new Moore Transition object
     *
     * @param input
     * @param target
     */
    MooreTransition(const QString &input, const QString &target)
        : input(input), target(target) {}
    /**
     * @brief Get the Input object
     *
     * @return QString
     */
    QString getInput() const { return input; }
    /**
     * @brief Get the Target object
     *
     * @return QString
     */
    QString getTarget() const { return target; }
    /**
     * @brief Set the Input object
     *
     * @param command
     */
    void setInput(QString command)
    {
        input = command;
    }

private:
    /// @brief
    QString input;
    /// @brief
    QString target;
};
