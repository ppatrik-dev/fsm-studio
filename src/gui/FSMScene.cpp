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
#include "ForceDirectedLayout.h"
#include "../parser/MooreMachine.h"

FSMScene::FSMScene(QObject *parent)
    : QGraphicsScene{parent}, sceneMode(SELECT_MODE),
      firstSelectedState(nullptr)
{
}
void FSMScene::setMachine(MooreMachine *machine)
{
    this->machine = machine;
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
    std::shared_ptr<MooreState> mooreState = nullptr;
    emit createStateRequested(mooreState, label, "Output1");
    state->setMooreState(mooreState);
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

void FSMScene::addImportTransition(FSMState *firstSelectedState, FSMState *secondSelectedState)
{
    FSMTransition *transition = new FSMTransition(firstSelectedState, secondSelectedState);
    m_transitions.append(transition);
    if (firstSelectedState == secondSelectedState) {
        firstSelectedState->appendTransition(transition);
    }
    else {
        firstSelectedState->appendTransition(transition);
        secondSelectedState->appendTransition(transition);
    }
}
FSMState *FSMScene::getStateByName(const QString &name) const
{
    return m_states.value(name, nullptr);
}

void FSMScene::onClearScene()
{
    clearScene();
}

void FSMScene::addTransition(FSMState *state)
{
    if (!firstSelectedState)
    {
        state->setSelected(true);
        firstSelectedState = state;
    }
    else
    {
        FSMState *secondSelectedState = state;
        if (!firstSelectedState)
        {
            qWarning() << "firstSelectedState is null!";
            return;
        }
        if (!secondSelectedState)
        {
            qWarning() << "secondSelectedState is null!";
            return;
        }
        if (!firstSelectedState->getMooreState())
        {
            qWarning() << "MooreState in firstSelectedState is null!";
            return;
        }

        emit createTransitionRequest(firstSelectedState->getMooreState(), "", secondSelectedState->getLabel());

        FSMTransition *transition = new FSMTransition(firstSelectedState, secondSelectedState);
        m_transitions.append(transition);
        addItem(transition);

        if (firstSelectedState == secondSelectedState) {
            firstSelectedState->appendTransition(transition);
        }
        else {
            firstSelectedState->appendTransition(transition);
            secondSelectedState->appendTransition(transition);
        }

        emit itemSelected(firstSelectedState);
        emit addNewTransition(transition);
        sceneMode = SELECT_MODE;
        firstSelectedState = nullptr;
    }
}

void FSMScene::deleteTransition(FSMTransition *transition)
{
    if (!transition) return;

    FSMState *first = transition->getFirstState();
    FSMState *second = transition->getSecondState();
    // emit deleteTransitionRequested(first->getLabel(), second->getLabel());

    if (first)
        first->removeTransition(transition);
    if (second)
        second->removeTransition(transition);

    transition->setSelected(false);
    transition->setRow(nullptr);
    debug(transition);
    removeItem(transition);
    transition->setParentItem(nullptr);

    m_transitions.removeAll(transition);
    transition->deleteLater();
}

void FSMScene::deleteState(FSMState *state)
{
    QList<FSMTransition*> transitions = state->getTransitions();
    emit deleteStateRequested(state->getLabel());
    for (FSMTransition *transition : transitions)
    {
        transition->other(state)->removeTransitionRow(state->getLabel());
        deleteTransition(transition);
    }

    state->clearTransitionsRows();

    if (state->getLabel() == "A") {
        if (state->scene() == nullptr) {
            qDebug() << "NULLPTR";
        }
    }

    debug(state);
    removeItem(state);
    m_states.remove(state->getLabel());
    state->deleteLater();
}

void FSMScene::clearScene()
{
    QList<FSMState*> states = m_states.values();
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
            addTransition(state);
        }
        else
        {
            sceneMode = SELECT_MODE;
            firstSelectedState = nullptr;
        }
    }
    else if (sceneMode == DELETE_STATE_MODE)
    {
        if (FSMState *state = qgraphicsitem_cast<FSMState *>(item))
        {
            state->setSelected(true);
            if (state->isInitial())
                emit initialStateDeleted(nullptr);
            deleteState(state);
        }
        else
        {
            QGraphicsScene::mousePressEvent(event);
        }

        sceneMode = SELECT_MODE;
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
    clearScene();

    for (auto it = machine.states.cbegin(); it != machine.states.cend(); ++it)
    {
        const std::shared_ptr<MooreState> &state = it.value();
        QString name = it.key();
        addImportState(name, state);
    }

    for (FSMState *state : m_states)
    {
        for (const auto &transition : state->getMooreState()->transitions)
        {
            addImportTransition(state, getStateByName(transition.getTarget()));
        }
    }
    displayAutomaton(m_states.values(), m_transitions);
}

void FSMScene::displayAutomaton(const QList<FSMState *> &states, const QList<FSMTransition *> &transitions)
{
    ForceDirectedLayout layout;
    layout.applyLayout(states, transitions, 800, 600, 100);

    for (FSMState *state : states)
    {
        addItem(state);
    }

    for (FSMTransition *transition : transitions)
    {
        addItem(transition);
    }
}
void FSMScene::addConnects()
{
    connect(this, &FSMScene::createStateRequested,
            this->machine, &MooreMachine::createAndAddState);

    connect(this, &FSMScene::createTransitionRequest,
            this->machine, &MooreMachine::createTransition);
}

FSMTransition *FSMScene::createTransition(FSMState *firstState, FSMState *secondState)
{
    FSMTransition *transition = new FSMTransition(firstState, secondState);

    m_transitions.append(transition);

    if (firstState == secondState) {
        firstState->appendTransition(transition);
    }
    else {
        firstState->appendTransition(transition);
        secondState->appendTransition(transition);
    }
    addItem(transition);

    return transition;
}
