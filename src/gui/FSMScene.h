/**
 * @file FSMScene.h
 * @author Patrik Prochazka (xprochp00@vutbr.cz)
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Header file for FSMScene class
 * @version 2.0
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef FSMSCENE_H
#define FSMSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QMap>
#include <QDebug>
#include <QGraphicsLineItem>
#include <climits>
#include "FSMState.h"
#include "FSMTransition.h"
#include "../parser/MooreMachine.h"
#include "../parser/MooreState.h"

class MainWindow;

/**
 * @brief FSM Scene class, inherit from QGraphicsScene
 *
 */
class FSMScene : public QGraphicsScene
{
    Q_OBJECT

private:
    FSMState *firstSelectedState;
    QMap<QString, FSMState *> m_states;
    QList<FSMTransition *> m_transitions;
    MooreMachine *machine;
    FSMState *activeState;

    /**
     * @brief Enumeration for scene mode
     * 
     */
    enum sceneModeEnum
    {
        SELECT_MODE,
        ADD_TRANSITION_MODE,
        DELETE_STATE_MODE,
    };
    enum sceneModeEnum sceneMode;

    inline static bool debug = false;

public:
    /**
     * @brief Construct a new FSMScene object
     *
     * @param parent
     */
    explicit FSMScene(QObject *parent = nullptr);

    void clearScene();

    /**
     * @brief Clears the FSM scene
     *
     */
    void onClearScene()
    {
        clearScene();
    }

    /**
     * @brief Set the Machine object
     *
     * @param machine
     */
    void setMachine(MooreMachine *machine)
    {
        this->machine = machine;
    }

    /**
     * @brief Add signal-slot connection
     *
     */
    void addConnects();

    /**
     * @brief Remove empty condition transitions
     *
     */
    void removeEpsilonTransitions();

    /**
     * @brief Get FSM states in scene
     *
     * @return QMap<QString, FSMState *>
     */
    inline QMap<QString, FSMState *> getFSMStates() const
    {
        return m_states;
    }

    /**
     * @brief Get FSM transitions in scene
     *
     * @return QList<FSMTransition *>
     */
    inline QList<FSMTransition *> getTransitions() const
    {
        return m_transitions;
    }

    /**
     * @brief Generate the state label
     *
     * @return QString
     */
    inline QString getStateLabel()
    {
        for (char c = 'A'; c <= 'Z'; ++c)
        {
            QString label(c);
            if (!m_states.contains(label))
            {
                return label;
            }
        }

        for (int n = 0; n < INT_MAX; ++n)
        {
            for (char c = 'A'; c <= 'Z'; ++c)
            {
                QString label = QString(c) + QString::number(n);
                if (!m_states.contains(label))
                {
                    return label;
                }
            }
        }

        return QString();
    }

    /**
     * @brief Create new transition item
     *
     * @param firstState
     * @param secondState
     * @return FSMTransition*
     */
    FSMTransition *createTransition(FSMState *firstState, FSMState *secondState);

public:
    /**
     * @brief Delete transition item
     *
     * @param state
     */
    void deleteTransition(FSMTransition *transition, bool mooreDeleteFlag);

    /**
     * @brief Get the state item with name specified
     *
     * @param name
     * @return FSMState*
     */
    FSMState *getStateByName(const QString &name) const
    {
        return m_states.value(name, nullptr);
    }

    /**
     * @brief Debug print for deleting items
     *
     * @param item
     */
    void deleteDebug(QGraphicsItem *item);

    /**
     * @brief Save state transitions conditions
     *
     * @param state
     */
    void saveConditions(FSMState *state);

protected:
    /**
     * @brief Mouse press event override implementation
     *
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Add new state item
     *
     * @param pos
     */
    void addState(QPointF pos);

    /**
     * @brief Add new state item from import
     *
     * @param name
     * @param state
     */
    void addImportState(QString name, const std::shared_ptr<MooreState> &state);

    /**
     * @brief Add new transition item
     *
     * @param state
     */
    void addTransition(FSMState *state);

    /**
     * @brief Delete state item
     *
     * @param state
     */
    void deleteState(FSMState *state);

    /**
     * @brief Add new transition item from import
     *
     * @param firstSelectedState
     * @param secondSelectedState
     * @return FSMTransition*
     */
    FSMTransition *addImportTransition(FSMState *firstSelectedState, FSMState *secondSelectedState);

    /**
     * @brief Display FSM to scene from import
     *
     * @param states
     * @param transitions
     */
    void displayAutomaton(const QList<FSMState *> &states, const QList<FSMTransition *> &transitions);

    /**
     * @brief Create transition row from import
     *
     * @param state
     * @param transition
     * @return TransitionRowWidget*
     */
    TransitionRowWidget *createTransitionRow(FSMState *state, const MooreTransition &transition);

public slots:
    /**
     * @brief Add new state slot
     *
     * @param pos
     */
    void onAddState(const QPointF &pos);

    /**
     * @brief Add new transition slot
     *
     */
    void onAddTransition();

    /**
     * @brief Delete state slot
     *
     */
    void onDeleteState();

    /**
     * @brief Create machine from file slot
     *
     * @param machine
     */
    void createMachineFile(MooreMachine &machine);

    /**
     * @brief Set active state in simulation
     *
     * @param label
     */
    void setActiveState(const QString &label);

    /**
     * @brief Unset activa state from simulation
     *
     */
    void unsetActiveState();

signals:
    /**
     * @brief Initial state deleted signal
     *
     * @param state
     */
    void initialStateDeleted(FSMState *state);

    /**
     * @brief Item selected in scene changed signal
     *
     * @param item
     */
    void itemSelected(QGraphicsItem *item);

    /**
     * @brief Add new transition signal
     *
     * @param transition
     */
    void addNewTransition(FSMTransition *transition);

    /**
     * @brief Request create state signal
     *
     * @param state
     * @param stateName
     * @param output
     */
    void createStateRequested(std::shared_ptr<MooreState> &state, const QString &stateName, const QString &output);

    /**
     * @brief Request create transition signal
     *
     * @param state
     * @param action
     * @param targetName
     */
    void createTransitionRequest(const std::shared_ptr<MooreState> &state, const QString &action, const QString &targetName);

    /**
     * @brief Request delete state signal
     *
     * @param name
     */
    void deleteStateRequested(QString name);

    /**
     * @brief Request delete transition signal
     *
     * @param firstName
     * @param secondName
     */
    void deleteTransitionRequested(QString firstName, QString secondName);

    /**
     * @brief Request new transition row signal
     *
     * @param state
     * @param row
     */
    void newTransitionRowRequested(FSMState *state, TransitionRowWidget *&row);

    /**
     * @brief Request remove row and transition signal
     *
     * @param state
     * @param row
     */
    void requestRemoveRowAndTransition(FSMState *state, TransitionRowWidget *row);
};

#endif // FSMSCENE_H
