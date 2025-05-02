// File: FSMView.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMScene.h"
#include "FSMState.h"

#include <QPen>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

FSMScene::FSMScene(QObject *parent)
    : QGraphicsScene{parent},
    stateCounter(0), addTransitionMode(false)
{}

void FSMScene::onAddState(const QPointF &pos) {
    FSMState *state = new FSMState(getStateLabel());
    state->setPos(pos);
    addItem(state);
    m_FSMStates.append(state);
}

void FSMScene::onAddTransition() {
    addTransitionMode = true;
    fromSelectedState = nullptr;
}

void FSMScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (addTransitionMode) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        FSMState *state = qgraphicsitem_cast<FSMState*>(item);
        state->setSelected(true);

        if (state) {
            if (!fromSelectedState) {
                fromSelectedState = state;
            }
            else {
                FSMState *toSelectedState = state;

                FSMTransition *transition = new FSMTransition(fromSelectedState, toSelectedState);
                addItem(transition);

                fromSelectedState->addTransition(transition);
                toSelectedState->addTransition(transition);

                m_transitions.append(transition);

                addTransitionMode = false;
                fromSelectedState = nullptr;
            }
        }
    }
    else {
        QGraphicsScene::mousePressEvent(event);
    }
}

// void FSMScene::onAddTransition() {
//     QGraphicsLineItem *transition = new QGraphicsLineItem(
//         fromState->pos().x(), fromState->pos().y(),
//         toState->pos().x(), toState->pos().y()
//         );

//     transition->setPen(QPen(Qt::gray, 2));
//     addItem(transition);
//     m_transitions.append(transition);
// }

