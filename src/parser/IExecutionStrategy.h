/**
 * @file IExecutionStrategy.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Interface for defining execution strategies of Moore machine simulations
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "MooreMachine.h"
/**
 * @class IExecutionStrategy
 * @brief Abstract interface for Moore machine execution strategies.
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
