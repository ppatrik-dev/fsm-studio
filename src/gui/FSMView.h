// File: FSMView.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef FSMVIEW_H
#define FSMVIEW_H

#include <QGraphicsView>

class FSMView : public QGraphicsView {
    Q_OBJECT
public:
    explicit FSMView(QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

signals:
    void addStateRequested(const QPointF &pos);
    void addTransitionRequested();
};

#endif // FSMVIEW_H
