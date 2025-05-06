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
#include "../parser/MooreState.h"
#include <TransitionRowWidget.h>
#include <QVBoxLayout>

class FSMTransition;

class FSMState : public QGraphicsObject
{
private:
    bool m_initial;
    // bool m_new_transition;
    bool m_hovered;
    int m_radius;
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
    void saveConditions(QList<TransitionRowWidget *> conditionsRows);

    inline bool isInitial() const {
        return m_initial;
    }

    inline void setInitial(bool value) {
        m_initial = value;
        update();
    }

    // inline bool isNewTransition() const {
    //     return m_new_transition;
    // }

    // inline void setNewTransition(bool value) {
    //     m_new_transition = value;
    // }

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
