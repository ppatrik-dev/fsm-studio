/**
 * @file ForceDirectedLayout.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef FORCE_DIRECTED_LAYOUT_H
#define FORCE_DIRECTED_LAYOUT_H

#include <QList>
#include <QPointF>
#include <QMap>
#include <QGraphicsItem>
#include "FSMState.h"
#include "FSMTransition.h"

/**
 * @brief
 *
 */
class ForceDirectedLayout
{
public:
    /**
     * @brief Running ForceDirect algorithm on the layout (fsmScene)
     *
     * @param states
     * @param transitions
     * @param width
     * @param height
     * @param iterations
     */
    static void applyLayout(const QList<FSMState *> &states,
                            const QList<FSMTransition *> &transitions,
                            int width, int height, int iterations);
};

#endif
