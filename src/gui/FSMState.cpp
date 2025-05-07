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

void FSMState::saveConditions(QList<TransitionRowWidget*> conditionsRows) {
    m_conditions.clear();

    for (auto row : conditionsRows) {
        m_conditions.append({row->getConditionText(), row->getToStateText()});
    }
}

void FSMState::removeCondition(QString toState) {
    m_conditions.erase(
        std::remove_if(m_conditions.begin(), m_conditions.end(),
            [toState](const QPair<QString, QString> &pair) {
                return pair.second == toState;
            }),
        m_conditions.end()
    );
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
