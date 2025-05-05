#ifndef FSMTRANSITION_H
#define FSMTRANSITION_H

// File: FSMState.h
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMState.h"

class FSMTransition : public QGraphicsObject
{
private:
    FSMState *m_firstState;
    FSMState *m_secondState;
    QLineF m_line;

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
};

#endif // FSMTRANSITION_H
