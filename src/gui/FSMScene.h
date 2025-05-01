// File: FSMScene.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef FSMSCENE_H
#define FSMSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QGraphicsLineItem>
#include "FSMState.h"

class FSMScene : public QGraphicsScene {
    Q_OBJECT

private:
    int stateCounter;
    QList<FSMState*> m_FSMStates;
    QList<QGraphicsLineItem*> m_transitions;

public:
    explicit FSMScene(QObject *parent = nullptr);

    inline QList<FSMState*> getFSMStates() const {
        return m_FSMStates;
    }

    inline QList<QGraphicsLineItem*> getTransitions() const {
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

public slots:
    void onAddState(const QPointF &pos);
    // void onAddTransition();
};

#endif // FSMSCENE_H
