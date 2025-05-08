#ifndef FSMTRANSITION_H
#define FSMTRANSITION_H

// File: FSMState.h
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMState.h"
#include "TransitionRowWidget.h"

class FSMState;
class TransitionRowWidget;

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
    explicit FSMTransition(FSMState *from, FSMState *to);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updatePosition();

    FSMState *getFirstState() const
    {
        return m_firstState;
    }

    FSMState *getSecondState() const
    {
        return m_secondState;
    }
    FSMState *target() const;

    FSMState *other(FSMState *state) const {
        return (state == m_firstState) ? m_secondState : m_firstState;
    }

    TransitionRowWidget* getRow() const {
        return m_row;
    }

    void setRow(TransitionRowWidget *row) {
        m_row = row;
    }

    QString getCondition() const;
};

#endif // FSMTRANSITION_H
