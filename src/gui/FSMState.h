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

class TransitionRowWidget;

class FSMTransition;

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
    
    void setActive(bool value) {
        m_active = value;
        update();
    }

    bool isActive() const {
        return m_active;
    }

    void clearTransitionsRows();

    void updateOutput(QString value) {
        setOutput(value);

        m_state->setOutput(value);
    }

    void setOutput(QString value) {
        m_output = value;
    }

    QString getOutput() const {
        return m_output;
    }

    inline bool isInitial() const {
        return m_initial;
    }

    inline void setInitial(bool value) {
        m_initial = value;
        update();
    }

    inline QString getLabel() const
    {
        return m_label;
    }

    inline QList<TransitionRowWidget*>& getTransitionsRows()
    {
        return m_transitionsRows;
    }

    inline QList<QPair<QString, QString>> getTransitionsConditions() const
    {
        return m_transitionsConditions;
    }

    inline QList<FSMTransition *> getTransitions() const
    {
        return m_transitions;
    }

    void removeTransitionRow(QString toState);

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
