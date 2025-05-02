#ifndef FSMTRANSITION_H
#define FSMTRANSITION_H

#include <QGraphicsItem>
#include "FSMState.h"

class FSMTransition : public QGraphicsItem {
private:
    FSMState *m_fromState;
    FSMState *m_toState;
    QLineF m_line;

public:
    FSMTransition(FSMState *from, FSMState *to)
        : m_fromState(from), m_toState(to) {
        setZValue(-1);
        updatePosition();
    }

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updatePosition();
};

#endif // FSMTRANSITION_H
