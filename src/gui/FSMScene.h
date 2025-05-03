// File: FSMScene.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef FSMSCENE_H
#define FSMSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QGraphicsLineItem>
#include "FSMState.h"
#include "FSMTransition.h"

class FSMScene : public QGraphicsScene {
    Q_OBJECT

private:
    int stateCounter;

    FSMState *firstSelectedState;
    QList<FSMState*> m_states;
    QList<FSMTransition*> m_transitions;
    enum sceneModeEnum {SELECT_MODE, ADD_TRANSITION_MODE, DELETE_STATE_MODE, DELETE_TRANSITION_MODE};
    enum sceneModeEnum sceneMode;

public:
    explicit FSMScene(QObject *parent = nullptr);

    inline QList<FSMState*> getFSMStates() const {
        return m_states;
    }

    inline QList<FSMTransition*> getTransitions() const {
        return m_transitions;
    }

    inline QString getStateLabel() {
        QString label;
        QChar letter = QChar('A' + (stateCounter % 26));

        if (stateCounter < 26) {
            label = QString(letter);
        }
        else {
            int number = stateCounter / 26;
            label = QString("%1%2").arg(letter).arg(number);
        }

        stateCounter++;

        return label;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void addState(QPointF pos);
    void addTransition(FSMState *state);
    void deleteTransition(FSMTransition *transition);
    void deleteState(FSMState *state);

public slots:
    void onAddState(const QPointF &pos);
    void onAddTransition();
    void onDeleteState();
    void onDeleteTransition();

signals:
    void itemSelected(QGraphicsItem *item);
};

#endif // FSMSCENE_H
