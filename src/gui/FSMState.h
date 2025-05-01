// File: FSMState.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef FSMSTATE_H
#define FSMSTATE_H

#include <QGraphicsItem>
#include <QString>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class FSMState : public QGraphicsItem
{
public:
    explicit FSMState(const QString &label);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QString m_label;
};

#endif // FSMSTATE_H
