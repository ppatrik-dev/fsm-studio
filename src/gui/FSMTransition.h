/**
 * @file FSMTransition.h
 * @author Patrik Prochazka (xprochp00@vutbr.cz)
 * @brief Header file for FSMTransition class
 * @version 0.1
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef FSMTRANSITION_H
#define FSMTRANSITION_H

#include "FSMState.h"
#include "TransitionRowWidget.h"

class FSMState;
class TransitionRowWidget;

/**
 * @brief FSMTransition class, inherit from QGraphicsObject
 * 
 */
class FSMTransition : public QGraphicsObject
{
private:
    FSMState *m_firstState = nullptr;
    FSMState *m_secondState = nullptr;
    QLineF m_line;
    TransitionRowWidget *m_row = nullptr;

public:
    enum
    {
        Type = UserType + 2
    };
    int type() const override { return Type; }

public:
    /**
     * @brief Construct a new FSMTransition object
     * 
     * @param from 
     * @param to 
     */
    explicit FSMTransition(FSMState *from, FSMState *to);

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
     * @brief Update item position
     * 
     */
    void updatePosition();

    /**
     * @brief Get the First State object
     * 
     * @return FSMState* 
     */
    FSMState *getFirstState() const
    {
        return m_firstState;
    }

    /**
     * @brief Get the Second State object
     * 
     * @return FSMState* 
     */
    FSMState *getSecondState() const
    {
        return m_secondState;
    }

    /**
     * @brief Get the Target State object
     * 
     * @return FSMState* 
     */
    FSMState *target() const
    {
        return m_secondState;
    }

    /**
     * @brief Get the Other State object
     * 
     * @param state 
     * @return FSMState* 
     */
    FSMState *other(FSMState *state) const {
        return (state == m_firstState) ? m_secondState : m_firstState;
    }

    /**
     * @brief Get the Row object
     * 
     * @return TransitionRowWidget* 
     */
    TransitionRowWidget* getRow() const {
        return m_row;
    }

    /**
     * @brief Set the Row object
     * 
     * @param row 
     */
    void setRow(TransitionRowWidget *row) {
        m_row = row;
    }
    
    /**
     * @brief Get the Condition string
     * 
     * @return QString 
     */
    QString getCondition() const;
};

#endif // FSMTRANSITION_H
