// File: FSMState.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef FSMSTATE_H
#define FSMSTATE_H

#include <QGraphicsItem>
#include <QString>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class FSMTransition; // Forward declaration

class FSMState : public QGraphicsItem
{
public:
    explicit FSMState(const QString &label);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void addTransition(FSMTransition *transition);
private:
    QString m_label;
    QList<FSMTransition*> m_transitions;
};

#endif // FSMSTATE_H
