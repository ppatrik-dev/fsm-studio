// File: FSMState.h
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMTransition.h"

FSMTransition::FSMTransition(FSMState *first, FSMState *second)
    : m_firstState(first), m_secondState(second)
{
    setZValue(-1);
    updatePosition();
    setCacheMode(DeviceCoordinateCache);
}

void FSMTransition::updatePosition()
{
    m_line = QLineF(m_firstState->pos(), m_secondState->pos());
    prepareGeometryChange();
    update();
}

QRectF FSMTransition::boundingRect() const
{
    return QRectF(m_line.p1(), QSizeF(m_line.dx(), m_line.dy())).normalized().adjusted(-5, -5, 5, 5);
}

void FSMTransition::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QPen(Qt::gray, 2));
    painter->drawLine(m_line);
}

FSMState *FSMTransition::target() const
{
    return m_secondState;
}
