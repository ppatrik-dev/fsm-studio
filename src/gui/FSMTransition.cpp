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
    prepareGeometryChange();

    if (m_firstState == m_secondState) {
        setPos(m_firstState->pos());
    } else {
        m_line = QLineF(m_firstState->pos(), m_secondState->pos());
    }

    update();
}

QRectF FSMTransition::boundingRect() const
{
    if (m_firstState == m_secondState) {
        return QRectF(-35, -85, 70, 70);
    }
    return QRectF(m_line.p1(), QSizeF(m_line.dx(), m_line.dy())).normalized().adjusted(-5, -5, 5, 5);
}

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

FSMState *FSMTransition::target() const
{
    return m_secondState;
}

QString FSMTransition::getCondition() const
{
    if (m_row) {
        return m_row->getConditionText();
    }
    return QString();
}