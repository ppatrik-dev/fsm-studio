// File: FSMState.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMState.h"
#include "FSMTransition.h"
#include "ConditionRowWidget.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>

FSMState::FSMState(const QString &label)
    : m_label(label)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
}

QRectF FSMState::boundingRect() const {
    return QRectF(-30, -30, 60, 60);
}

void FSMState::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QRectF rect = boundingRect();
    QColor outlineColor = isSelected() ? QColor(0, 204, 153) : QColor(51, 153, 102);

    QColor baseColor(40, 40, 40);
    QColor fillColor = m_hovered ? baseColor.lighter(130) : baseColor;
    painter->setBrush(fillColor);
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
            transition->updatePosition();
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void FSMState::saveConditions(QList<ConditionRowWidget*> conditionsRows) {
    m_conditions.clear();

    for (auto row : conditionsRows) {
        m_conditions.append({row->getIfText(), row->getThenText()});
    }
}

void FSMState::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    m_hovered = true;
    update();  // triggers repaint
    QGraphicsItem::hoverEnterEvent(event);
}

void FSMState::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    m_hovered = false;
    update();  // triggers repaint
    QGraphicsItem::hoverLeaveEvent(event);
}
