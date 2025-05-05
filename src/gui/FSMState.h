// File: FSMState.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef FSMSTATE_H
#define FSMSTATE_H

#include <QGraphicsObject>
#include <QPair>
#include <QString>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "parser/MooreState.h"
#include <ConditionRowWidget.h>
#include <QVBoxLayout>

class FSMTransition;

class FSMState : public QGraphicsObject
{
private:
    bool m_hovered = false;
    QString m_label;
    QList<FSMTransition *> m_transitions;
    std::shared_ptr<MooreState> m_state;
    QList<QPair<QString, QString>> m_conditions;

public:
    QPointF m_displacement;
    enum
    {
        Type = UserType + 1
    };
    int type() const override { return Type; }

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
    void saveConditions(QList<ConditionRowWidget *> conditionsRows);
    inline QString getLabel() const
    {
        return m_label;
    }

    inline QList<QPair<QString, QString>> getConditions() const
    {
        return m_conditions;
    }

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

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // FSMSTATE_H
