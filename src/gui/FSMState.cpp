// File: FSMState.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMState.h"
#include "FSMTransition.h"
#include "TransitionRowWidget.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>

FSMState::FSMState(const QString &label)
    : m_initial(false), m_hovered(false),
      m_radius(0), m_label(label)
{
    QFont font;
    font.setPointSize(16);
    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(label);
    m_radius = std::max(30, textWidth / 2 + 10);

    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
}

QRectF FSMState::boundingRect() const {
    return QRectF(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
}

void FSMState::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QRectF rect = boundingRect();

    QColor outlineColor = isInitial() ? QColor(0, 204, 153) : QColor(51, 153, 102);
    outlineColor = isSelected() ? QColor(161, 221, 192) : outlineColor;

    QColor baseColor(40, 40, 40);
    QColor fillColor = m_hovered ? baseColor.lighter(130) : baseColor;
    painter->setBrush(fillColor);

    int outlineWidth = isInitial() ? 3 : 2;
    QPen pen(outlineColor, outlineWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter->setPen(pen);
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

void FSMState::saveConditions() {
    m_transitionsConditions.clear();

    auto rows = m_transitionsRows;
    for (TransitionRowWidget *row : rows) {
        QString conditionText = row->getConditionText();
        QString toStateText = row->getToStateText();

        if (conditionText.isEmpty() || toStateText.isEmpty()) {
            row->requestRemove(row);
        }

        m_transitionsConditions.append({conditionText, toStateText});
    }
}

void FSMState::removeTransitionRow(QString toState) {
    auto rows = m_transitionsRows;
    for (auto row : rows) {
        if (row->getToStateText() == toState) {
            m_layout->removeWidget(row);
            m_transitionsRows.removeAll(row);
            row->deleteLater();
        }
    }
}

void FSMState::clearTransitionsRows() {
    for (auto row : m_transitionsRows)
    {
        if (row) {
            FSMState::m_layout->removeWidget(row);
            row->deleteLater();
        }
    }

    m_transitionsRows.clear();
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
