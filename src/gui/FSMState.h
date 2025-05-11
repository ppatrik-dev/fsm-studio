/**
 * @file FSMState.h
 * @author Patrik Prochazka (xprochp00@vutbr.cz)
 * @brief Header file for FSMState class
 * @version 2.0
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef FSMSTATE_H
#define FSMSTATE_H

#include <QGraphicsObject>
#include <QPair>
#include <QString>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "../parser/MooreState.h"
#include <TransitionRowWidget.h>
#include <QVBoxLayout>
#include <memory>

class TransitionRowWidget;
class FSMTransition;

/**
 * @brief FSMState class, inherit from QGraphicsObject
 * 
 */
class FSMState : public QGraphicsObject
{
private:
    bool m_initial;
    bool m_hovered;
    bool m_active;
    int m_radius;
    QString m_label;
    QString m_output;
    QList<FSMTransition *> m_transitions;
    std::shared_ptr<MooreState> m_state;
    QList<QPair<QString, QString>> m_transitionsConditions;
    QList<TransitionRowWidget*> m_transitionsRows;

public:
    inline static QVBoxLayout *m_layout = nullptr;

public:
    enum
    {
        Type = UserType + 1
    };
    int type() const override { return Type; }

    /**
     * @brief Set the Moore state
     * 
     * @param state 
     */
    void setMooreState(const std::shared_ptr<MooreState> &state)
    {
        m_state = state;
    }

    /**
     * @brief Get the Moore state
     * 
     * @return std::shared_ptr<MooreState> 
     */
    std::shared_ptr<MooreState> getMooreState() const
    {
        return m_state;
    }

public:
    /**
     * @brief Construct a new FSMState object
     * 
     * @param label 
     */
    explicit FSMState(const QString &label);

    /**
     * @brief Compute bounding rectangle
     * 
     * @return QRectF 
     */
    QRectF boundingRect() const override;

    /**
     * @brief Paints the item
     * 
     * @param painter 
     * @param option 
     * @param widget 
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    
    /**
     * @brief Item changes
     * 
     * @param change 
     * @param value 
     * @return QVariant 
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    
    /**
     * @brief Set the active status
     * 
     * @param value 
     */
    void setActive(bool value) {
        m_active = value;
        update();
    }

    /**
     * @brief Get if the object has active status
     * 
     * @return true 
     * @return false 
     */
    bool isActive() const {
        return m_active;
    }

    /**
     * @brief Clear transitions condition rows 
     * 
     */
    void clearTransitionsRows();

    /**
     * @brief Update state output 
     * 
     * @param value 
     */
    void updateOutput(QString value) {
        setOutput(value);

        m_state->setOutput(value);
    }

    /**
     * @brief Set the state output
     * 
     * @param value 
     */
    void setOutput(QString value) {
        m_output = value;
    }

    /**
     * @brief Get the state output
     * 
     * @return QString 
     */
    QString getOutput() const {
        return m_output;
    }

    /**
     * @brief Get if the state is initial
     * 
     * @return true 
     * @return false 
     */
    inline bool isInitial() const {
        return m_initial;
    }

    /**
     * @brief Set the initial status
     * 
     * @param value 
     */
    inline void setInitial(bool value) {
        m_initial = value;
        update();
    }

    /**
     * @brief Get the state label
     * 
     * @return QString 
     */
    inline QString getLabel() const
    {
        return m_label;
    }

    /**
     * @brief Get the state transitions rows list
     * 
     * @return QList<TransitionRowWidget*>& 
     */
    inline QList<TransitionRowWidget*>& getTransitionsRows()
    {
        return m_transitionsRows;
    }

    /**
     * @brief Get the state transitions conditions list
     * 
     * @return QList<QPair<QString, QString>> 
     */
    inline QList<QPair<QString, QString>> getTransitionsConditions() const
    {
        return m_transitionsConditions;
    }

    /**
     * @brief Get the transitions items list
     * 
     * @return QList<FSMTransition *> 
     */
    inline QList<FSMTransition *> getTransitions() const
    {
        return m_transitions;
    }

    /**
     * @brief Remove transition condition row
     * 
     * @param toState 
     */
    void removeTransitionRow(QString toState);

    /**
     * @brief Append transition item to transitions list
     * 
     * @param transition 
     */
    inline void appendTransition(FSMTransition *transition)
    {
        m_transitions.append(transition);
    }

    /**
     * @brief Remove transition item from transitions list
     * 
     * @param transition 
     */
    inline void removeTransition(FSMTransition *transition)
    {
        m_transitions.removeAll(transition);
    }

protected:
    /**
     * @brief Hover event override implementation
     * 
     * @param event 
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    /**
     * @brief Hover leave event override implementation
     * 
     * @param event 
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // FSMSTATE_H
