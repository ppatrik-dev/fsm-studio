// File: FSMView.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef FSMVIEW_H
#define FSMVIEW_H

#include <QGraphicsView>
#include "FSMScene.h"

class FSMView : public QGraphicsView {
    Q_OBJECT
private:
    double m_currentScale = 1.0;

public:
    explicit FSMView(QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

public slots:
    void zoomIn();
    void zoomOut();

signals:
    void zoomChanged(int percent);
    void addStateRequested(const QPointF &pos);
    void addTransitionRequested();
    void deleteStateRequested();
};

#endif // FSMVIEW_H
