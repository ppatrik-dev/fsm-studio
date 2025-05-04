// File: FSMView.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMScene.h"
#include "FSMState.h"
#include <QRandomGenerator>
#include <QPen>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

FSMScene::FSMScene(QObject *parent)
    : QGraphicsScene{parent},
      m_labelCount(0), sceneMode(SELECT_MODE)
{
}

void FSMScene::onAddState(const QPointF &pos)
{
    addState(pos);
}

void FSMScene::onAddTransition()
{
    if (m_states.count() < 2)
    {
        qDebug() << "Warning: Cannot create transition, 2 states needed\n";
        return;
    }

    sceneMode = ADD_TRANSITION_MODE;
    firstSelectedState = nullptr;
}

void FSMScene::onDeleteState()
{
    sceneMode = DELETE_STATE_MODE;
}

void FSMScene::onDeleteTransition()
{
    sceneMode = DELETE_TRANSITION_MODE;
}

void FSMScene::addState(QPointF pos)
{
    QString label = getStateLabel();
    FSMState *state = new FSMState(label);
    m_states.insert(label, state);
    state->setPos(pos);
    state->setSelected(true);
    addItem(state);
    emit itemSelected(state);
}

void FSMScene::addImportState(QString name, const std::shared_ptr<MooreState> &mooreState)
{
    FSMState *state = new FSMState(name);
    state->setMooreState(mooreState);
    m_states.insert(name, state);
}

void FSMScene::onClearScene()
{
    clear();
}

void FSMScene::addTransition(FSMState *state)
{
    if (!firstSelectedState)
    {
        firstSelectedState = state;
    }
    else
    {
        FSMState *secondSelectedState = state;

        FSMTransition *transition = new FSMTransition(firstSelectedState, secondSelectedState);
        m_transitions.append(transition);
        addItem(transition);

        firstSelectedState->appendTransition(transition);
        secondSelectedState->appendTransition(transition);

        sceneMode = SELECT_MODE;
        firstSelectedState = nullptr;

        transition->setSelected(true);
        emit itemSelected(transition);
    }
}

void FSMScene::deleteTransition(FSMTransition *transition)
{
    FSMState *first = transition->getFirstState();
    FSMState *second = transition->getSecondState();

    if (first)
        first->removeTransition(transition);
    if (second)
        second->removeTransition(transition);

    removeItem(transition);
    m_transitions.removeAll(transition);
    delete transition;
}

void FSMScene::deleteState(FSMState *state)
{
    m_labelList.append(state->getLabel());

    auto transitions = state->getTransitions();
    for (FSMTransition *transition : transitions)
    {
        deleteTransition(transition);
    }

    removeItem(state);
    m_states.remove(state->getLabel());
    delete state;
}

void FSMScene::clear()
{
    auto states = m_states.values();
    for (FSMState *state : states)
    {
        deleteState(state);
    }
}

void FSMScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (sceneMode == ADD_TRANSITION_MODE)
    {
        if (FSMState *state = qgraphicsitem_cast<FSMState *>(item))
        {
            state->setSelected(true);
            addTransition(state);
        }
        else
        {
            sceneMode = SELECT_MODE;
            ;
            firstSelectedState = nullptr;
        }
    }
    else if (sceneMode == DELETE_STATE_MODE)
    {
        if (FSMState *state = qgraphicsitem_cast<FSMState *>(item))
        {
            state->setSelected(true);
            deleteState(state);
        }
        else
        {
            QGraphicsScene::mousePressEvent(event);
        }

        sceneMode = SELECT_MODE;
        ;
    }
    else if (sceneMode == DELETE_TRANSITION_MODE)
    {
        if (FSMTransition *transition = qgraphicsitem_cast<FSMTransition *>(item))
        {
            transition->setSelected(true);
            deleteTransition(transition);
        }
        else
        {
            QGraphicsScene::mousePressEvent(event);
        }

        sceneMode = SELECT_MODE;
    }
    else
    {
        QList<QGraphicsItem *> underCursor = items(event->scenePos(), Qt::IntersectsItemShape, Qt::DescendingOrder);
        QGraphicsItem *selected = nullptr;

        for (QGraphicsItem *item : underCursor)
        {
            if (item->type() == FSMTransition::Type)
            {
                selected = item;
                break;
            }
            else if (item->type() == FSMState::Type)
            {
                selected = item;
                break;
            }
        }

        emit itemSelected(selected);
        QGraphicsScene::mousePressEvent(event);
    }
}
void FSMScene::createMachineFile(MooreMachine &machine)
{
    for (auto it = machine.states.cbegin(); it != machine.states.cend(); ++it)
    {
        const std::shared_ptr<MooreState> &state = it.value();
        QString name = it.key();
        addImportState(name, state);
    }
}
