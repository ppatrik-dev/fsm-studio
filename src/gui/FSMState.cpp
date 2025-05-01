// File: FSMState.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMState.h"

FSMState::FSMState(const QString &label)
    : m_label(label)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
}

QRectF FSMState::boundingRect() const {
    return QRectF(-30, -30, 60, 60);
}

void FSMState::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->setBrush(QColor(40, 40, 40));
    painter->setPen(QPen(Qt::blue, 2));
    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::white);
    QFont font = painter->font();
    font.setPointSize(16);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignCenter, m_label);
}
