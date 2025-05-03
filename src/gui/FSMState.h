// File: FSMState.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef FSMSTATE_H
#define FSMSTATE_H

#include <QGraphicsItem>
#include <QString>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "parser/MooreState.h"

class FSMTransition;

class FSMState : public QGraphicsItem
{
private:
    QString m_label;
    QList<FSMTransition *> m_transitions;
    std::shared_ptr<MooreState> m_state;

public:
    enum
    {
        Type = UserType + 1
    };
    int type() const override { return Type; }

    QString getLabel() const
    {
        return m_label;
    }

    void setMooreState(const std::shared_ptr<MooreState> &state)
    {
        m_state = state;
    }

    std::shared_ptr<MooreState> getMooreState() const
    {
        return m_state;
    }

public:
    explicit FSMState(const QString &label);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    inline QList<FSMTransition *> getTransitions() const
    {
        return m_transitions;
    }

    inline void appendTransition(FSMTransition *transition)
    {
        m_transitions.append(transition);
    }

    inline void removeTransition(FSMTransition *transition)
    {
        m_transitions.removeAll(transition);
    }
};

#endif // FSMSTATE_H
