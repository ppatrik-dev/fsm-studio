/**
 * @file FSMTransition.cpp
 * @author Patrik Prochazka (xprochp00@vutbr.cz)
 * @brief Source file for FSMTransition class
 * @version 2.0
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "FSMTransition.h"

/**
 * @details 
 * Construct new transition object, setting some properties
 */
FSMTransition::FSMTransition(FSMState *first, FSMState *second)
    : m_firstState(first), m_secondState(second)
{
    setZValue(-1);
    updatePosition();
    setCacheMode(DeviceCoordinateCache);
}

/**
 * @details
 * Update transition position in scene
 */
void FSMTransition::updatePosition()
{
    prepareGeometryChange();

    if (m_firstState == m_secondState) {
        setPos(m_firstState->pos());
    } else {
        m_line = QLineF(m_firstState->pos(), m_secondState->pos());
    }

    update();
}

/**
 * @details
 * Computing item bounding rectangle
 */
QRectF FSMTransition::boundingRect() const
{
    if (m_firstState == m_secondState) {
        return QRectF(-35, -85, 70, 70);
    }
    return QRectF(m_line.p1(), QSizeF(m_line.dx(), m_line.dy())).normalized().adjusted(-5, -5, 5, 5);
}

/**
 * @details
 * Paint the transition item to scene
 */
void FSMTransition::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::gray, 2));

    if (m_firstState == m_secondState) {
        QRectF loopRect(-30, -80, 60, 60);
        painter->drawArc(loopRect, 0, 360 * 16);
    } else {
        painter->drawLine(m_line);
    }
}

/**
 * @details
 * Return saved condition row
 */
QString FSMTransition::getCondition() const
{
    if (m_row) {
        return m_row->getConditionText();
    }
    return QString();
}