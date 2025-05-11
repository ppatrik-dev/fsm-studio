/**
 * @file IMooreState.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Interface for defining Moore machine states.
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <QString>
/**
 * @class IMooreState
 * @brief Abstract interface representing a state in a Moore machine.
 */
class IMooreState
{
public:
    /**
     * @brief Destroy the IMooreState object
     *
     */
    virtual ~IMooreState() = default;
    /**
     * @brief Get the Name object
     *
     * @return QString
     */
    virtual QString getName() const = 0;
    /**
     * @brief Get the Output object
     *
     * @return QString
     */
    virtual QString getOutput() const = 0;
    /**
     * @brief Add transition
     *
     * @param input condition
     * @param target where go next
     */
    virtual void addTransition(const QString &input, const QString &target) = 0;
};