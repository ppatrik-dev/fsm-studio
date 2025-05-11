/**
 * @file FSMState.cpp
 * @author Patrik Prochazka (xprochp00@vutbr.cz)
 * @brief Source file for FSMState class
 * @version 2.0
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "FSMState.h"
#include "FSMTransition.h"
#include "TransitionRowWidget.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>

/**
 * @details
 * Constructs new State object and set its properties
 */
FSMState::FSMState(const QString &label)
    : m_initial(false), m_hovered(false), m_active(false),
      m_radius(0), m_label(label)
{
    QFont font;
    font.setPointSize(16);
    QFontMetrics metrics(font);
    int textWidth = metrics.width(label);;
    m_radius = std::max(30, textWidth / 2 + 10);

    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
}

/**
 * @details
 * Compute state bounding rectangle
 */
QRectF FSMState::boundingRect() const
{
    return QRectF(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
}

/**
 * @details
 * Paint the state item to scene 
 */
void FSMState::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QRectF rect = boundingRect();

    QColor outlineColor = isInitial() ? QColor(0, 204, 153) : QColor(51, 153, 102);
    outlineColor = isSelected() ? QColor(161, 221, 192) : outlineColor;

    QColor baseColor = isActive() ? QColor(51, 153, 102) : QColor (40, 40, 40);
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

/**
 * @details
 * Update state item in scene
 */
QVariant FSMState::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged)
    {
        for (FSMTransition *transition : m_transitions)
        {
            transition->updatePosition();
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

/**
 * @details
 * Remove transition condition row of specified state
 */
void FSMState::removeTransitionRow(QString toState)
{
    auto rows = m_transitionsRows;
    for (auto row : rows)
    {
        if (row->getToStateText() == toState)
        {
            m_layout->removeWidget(row);
            m_transitionsRows.removeAll(row);
            row->deleteLater();
        }
    }
}

/**
 * @details
 * Clear all transition condition rows of state object
 */
void FSMState::clearTransitionsRows()
{
    for (auto row : m_transitionsRows)
    {
        if (row)
        {
            FSMState::m_layout->removeWidget(row);
            row->deleteLater();
        }
    }

    m_transitionsRows.clear();
}

void FSMState::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_hovered = true;
    update();
    QGraphicsItem::hoverEnterEvent(event);
}

void FSMState::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_hovered = false;
    update();
    QGraphicsItem::hoverLeaveEvent(event);
}
