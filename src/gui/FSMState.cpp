// File: FSMState.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMState.h"
#include "FSMTransition.h"

FSMState::FSMState(const QString &label)
    : m_label(label)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
}

void FSMState::addTransition(FSMTransition *transition) {
    if (!m_transitions.contains(transition))
        m_transitions.append(transition);
}

QRectF FSMState::boundingRect() const {
    return QRectF(-30, -30, 60, 60);
}

void FSMState::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QRectF rect = boundingRect();
    QColor outlineColor = isSelected() ? QColor(102, 204, 255) : Qt::blue;

    painter->setBrush(QColor(40, 40, 40));
    painter->setPen(QPen(outlineColor, 2));
    painter->drawEllipse(rect);

    painter->setPen(Qt::white);
    QFont font = painter->font();
    font.setPointSize(16);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter, m_label);
}

QVariant FSMState::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionHasChanged) {
        for (FSMTransition *transition : m_transitions) {
            transition->updatePosition(); // Update the position of all transitions connected to this state
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
