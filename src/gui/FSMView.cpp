// File: FSMView.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMView.h"
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QGraphicsScene>
#include <QContextMenuEvent>

FSMView::FSMView(QWidget *parent) : QGraphicsView(parent) {
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::TextAntialiasing);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

void FSMView::zoomIn() {
    if (m_currentScale < 5.0) {
        double factor = 1.15;
        scale(factor, factor);
        m_currentScale *= factor;
        emit zoomChanged(int(m_currentScale * 100));
    }
}

void FSMView::zoomOut() {
    if (m_currentScale > 0.2) {
        double factor = 1.15;
        scale(1.0 / factor, 1.0 / factor);
        m_currentScale /= factor;
        emit zoomChanged(int(m_currentScale * 100));
    }
}

void FSMView::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);

    QAction *addStateAction = new QAction("Add State", this);
    QAction *addTransitionAction = new QAction("Add Transition", this);
    QAction *deleteStateAction = new QAction("Delete State", this);

    connect(addStateAction, &QAction::triggered, this, [=]() {
        emit addStateRequested(mapToScene(event->pos()));
    });

    connect(addTransitionAction, &QAction::triggered, this, [=]() {
        emit addTransitionRequested();
    });

    connect(deleteStateAction, &QAction::triggered, this, [=]() {
        emit deleteStateRequested();
    });

    menu.addAction(addStateAction);
    menu.addAction(addTransitionAction);
    menu.addAction(deleteStateAction);

    menu.exec(event->globalPos());
}
