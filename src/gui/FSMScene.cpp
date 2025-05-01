// File: FSMView.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMScene.h"
#include "FSMState.h"
// File: FSMScene.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include <QPen>
#include <QGraphicsLineItem>
#include <QDebug>

FSMScene::FSMScene(QObject *parent)
    : QGraphicsScene{parent}, stateCounter(0)
{}

void FSMScene::onAddState(const QPointF &pos) {
    FSMState *state = new FSMState(getStateLabel());
    state->setPos(pos);
    addItem(state);
    m_FSMStates.append(state);
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

