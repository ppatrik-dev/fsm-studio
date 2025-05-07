// File: FSMScene.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef FSMSCENE_H
#define FSMSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QMap>
#include <QGraphicsLineItem>
#include <climits>
#include "FSMState.h"
#include "FSMTransition.h"
#include "../parser/MooreMachine.h"
#include "../parser/MooreState.h"

class FSMScene : public QGraphicsScene
{
    Q_OBJECT

private:
    FSMState *firstSelectedState;
    QMap<QString, FSMState *> m_states;
    QList<FSMTransition *> m_transitions;
    MooreMachine *machine;
    enum sceneModeEnum
    {
        SELECT_MODE,
        ADD_TRANSITION_MODE,
        DELETE_STATE_MODE,
        DELETE_TRANSITION_MODE
    };
    enum sceneModeEnum sceneMode;

public:
    explicit FSMScene(QObject *parent = nullptr);
    void clearScene();
    void setMachine(MooreMachine *machine);
    void addConnects();

    inline QMap<QString, FSMState *> getFSMStates() const
    {
        return m_states;
    }

    inline QList<FSMTransition *> getTransitions() const
    {
        return m_transitions;
    }

    inline QString getStateLabel()
    {
        for (char c = 'A'; c <= 'Z'; ++c) {
            QString label(c);
            if (!m_states.contains(label)) {
                return label;
            }
        }

        for (int n = 0; n < INT_MAX; ++n) {
            for (char c = 'A'; c <= 'Z'; ++c) {
                QString label = QString(c) + QString::number(n);
                if (!m_states.contains(label)) {
                    return label;
                }
            }
        }
    }

    FSMTransition* createTransition(FSMState *firstState, FSMState *secondState);

public:
    void drawInitialArrow(FSMState *state);
    void deleteTransition(FSMTransition *transition);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void addState(QPointF pos);
    void addImportState(QString name, const std::shared_ptr<MooreState> &state);
    void addTransition(FSMState *state);
    void deleteState(FSMState *state);
    void addImportTransition(FSMState *firstSelectedState, FSMState *secondSelectedState);
    void displayAutomaton(const QList<FSMState *> &states, const QList<FSMTransition *> &transitions);
    FSMState *getStateByName(const QString &name) const;

public slots:
    void
    onAddState(const QPointF &pos);
    void onAddTransition();
    void onDeleteState();
    void onDeleteTransition();
    void createMachineFile(MooreMachine &machine);
    void onClearScene();

signals:
    void initialStateDeleted(FSMState *state);
    void itemSelected(QGraphicsItem *item);
    void addNewTransition(FSMTransition *transition);
    void createStateRequested(std::shared_ptr<MooreState> &state, const QString &stateName, const QString &output);
    void createTransitionRequest(const std::shared_ptr<MooreState> &state, const QString &action, const QString &targetname);
};

#endif // FSMSCENE_H
