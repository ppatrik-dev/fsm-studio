// File: FSMView.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMScene.h"
#include "FSMState.h"

#include <QPen>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

FSMScene::FSMScene(QObject *parent)
    : QGraphicsScene{parent},
    stateCounter(0), sceneMode(DEFAULT)
{}

void FSMScene::onAddState(const QPointF &pos) {
    FSMState *state = new FSMState(getStateLabel());
    m_states.append(state);
    state->setPos(pos);
    state->setSelected(true);
    addItem(state);

    emit itemSelected(state);
}

void FSMScene::onAddTransition() {
    if (stateCounter < 2) {
        qDebug() << "Warning: Cannot create transition, 2 states needed\n";
        return;
    }

    sceneMode = ADD;
    firstSelectedState = nullptr;
}

void FSMScene::onDeleteState() {
    sceneMode = DELETE;
}

void FSMScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (sceneMode == ADD) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        FSMState *state = nullptr;

        if (state = qgraphicsitem_cast<FSMState*>(item)) {
            state->setSelected(true);
            if (!firstSelectedState) {
                firstSelectedState = state;
            }
            else {
                FSMState *secondSelectedState = state;

                FSMTransition *transition = new FSMTransition(firstSelectedState, secondSelectedState);
                m_transitions.append(transition);
                transition->setSelected(true);
                addItem(transition);

                firstSelectedState->appendTransition(transition);
                secondSelectedState->appendTransition(transition);

                sceneMode = DEFAULT;
                firstSelectedState = nullptr;

                transition->setSelected(true);
                emit itemSelected(transition);
            }
        }
        else {
            sceneMode = DEFAULT;
            firstSelectedState = nullptr;
        }

        QGraphicsScene::mousePressEvent(event);
    }
    else if (sceneMode == DELETE) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        FSMState *state = nullptr;

        if (state = qgraphicsitem_cast<FSMState*>(item)) {
            state->setSelected(true);

            for (FSMTransition *transition : state->getTransitions()) {
                FSMState *first = transition->getFirstState();
                FSMState *second = transition->getSecondState();

                if (first) first->removeTransition(transition);
                if (second) second->removeTransition(transition);

                removeItem(transition);
                m_transitions.removeAll(transition);
                delete transition;

            }

            removeItem(state);
            m_states.removeAll(state);
            delete state;
        }
        else {
            QGraphicsScene::mousePressEvent(event);
        }

        sceneMode = DEFAULT;
    }
    else if (sceneMode == DEFAULT) {
        QList<QGraphicsItem*> underCursor = items(event->scenePos(), Qt::IntersectsItemShape, Qt::DescendingOrder);
        QGraphicsItem *selected = nullptr;

        for (QGraphicsItem *item : underCursor) {
            if (item->type() == FSMTransition::Type) {
                selected = item;
                break;
            }
            else if (item->type() == FSMState::Type) {
                selected = item;
                break;
            }
        }

        if (selected) selected->setSelected(true);
        emit itemSelected(selected);
        QGraphicsScene::mousePressEvent(event);
    }
}
