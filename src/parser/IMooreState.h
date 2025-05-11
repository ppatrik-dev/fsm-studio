/**
 * @file IMooreState.h
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
     * @brief
     *
     * @param input
     * @param target
     */
    virtual void addTransition(const QString &input, const QString &target) = 0;
};