#include "FSMTransition.h"

void FSMTransition::updatePosition() {
    // Recalculate the line based on the state positions
    m_line = QLineF(m_fromState->pos(), m_toState->pos());
    prepareGeometryChange(); // This notifies the QGraphicsItem that its geometry has changed.
}

QRectF FSMTransition::boundingRect() const {
    return QRectF(m_line.p1(), QSizeF(m_line.dx(), m_line.dy())).normalized().adjusted(-5, -5, 5, 5);
}

void FSMTransition::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setPen(QPen(Qt::gray, 2));
    painter->drawLine(m_line);
}
