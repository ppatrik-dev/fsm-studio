/**
 * @file IExecutionStrategy.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "MooreMachine.h"
/**
 * @brief
 *
 */
class IExecutionStrategy
{
public:
    /**
     * @brief Destroy the IExecutionStrategy object
     *
     */
    virtual ~IExecutionStrategy() = default;
    /**
     * @brief Start simulation
     *
     */
    virtual void Execute() = 0;
};
