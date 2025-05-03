// File: FSMView.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "FSMView.h"
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QGraphicsScene>
#include <QContextMenuEvent>
#include <QApplication>

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

    QAction *addStateAction = menu.addAction("Add State");
    QAction *addTransitionAction = menu.addAction("Add Transition");
    QAction *deleteStateAction = menu.addAction("Delete State");
    QAction *deleteTransitionAction = menu.addAction("Delete Transition");

    QAction *selected = menu.exec(event->globalPos());

    if (selected == addStateAction) {
        emit addStateRequested(mapToScene(event->pos()));
    } else if (selected == addTransitionAction) {
        emit addTransitionRequested();
    } else if (selected == deleteStateAction) {
        emit deleteStateRequested();
    } else if (selected == deleteTransitionAction) {
        emit deleteTransitionRequested();
    }
}
