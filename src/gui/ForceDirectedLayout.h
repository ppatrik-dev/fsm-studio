#ifndef FORCE_DIRECTED_LAYOUT_H
#define FORCE_DIRECTED_LAYOUT_H

#include <QList>
#include <QPointF>
#include <QMap>
#include <QGraphicsItem>
#include "FSMState.h"
#include "FSMTransition.h"

class ForceDirectedLayout
{
public:
    static void applyLayout(const QList<FSMState *> &states,
                            const QList<FSMTransition *> &transitions,
                            int width, int height, int iterations);
};

#endif
