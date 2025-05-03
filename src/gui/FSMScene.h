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
    FSMState *firstSelectedState;
    QList<FSMState*> m_states;
    QList<FSMTransition*> m_transitions;
    enum sceneModeEnum {SELECT_MODE, ADD_TRANSITION_MODE, DELETE_STATE_MODE, DELETE_TRANSITION_MODE};
    enum sceneModeEnum sceneMode;

    int m_labelCount;
    QList<QString> m_labelList;

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

        if (m_states.count() == 0) {
            m_labelCount = 0;
            m_labelList.clear();
        }

        if (m_labelList.count() > 1 && m_labelCount < 26) {
            std::sort(m_labelList.begin(), m_labelList.end());
        }

        if (m_states.count() < m_labelCount) {
            label = m_labelList.takeFirst();
        }
        else {
            int count = m_states.count();
            QChar letter = QChar('A' + (count % 26));

            if (count < 26) {
                label = QString(letter);
            }
            else {
                int number = count / 26;
                label = QString("%1%2").arg(letter).arg(number);
            }

            m_labelCount++;
        }

        return label;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void addState(QPointF pos);
    void addTransition(FSMState *state);
    void deleteTransition(FSMTransition *transition);
    void deleteState(FSMState *state);
    void clear();

public slots:
    void onAddState(const QPointF &pos);
    void onAddTransition();
    void onDeleteState();
    void onDeleteTransition();
    void onClearScene();

signals:
    void itemSelected(QGraphicsItem *item);
};

#endif // FSMSCENE_H
