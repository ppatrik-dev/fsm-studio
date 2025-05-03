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

void FSMView::wheelEvent(QWheelEvent *event) {
    if (!(event->modifiers() & Qt::ControlModifier)) {
        QGraphicsView::wheelEvent(event);
        return;
    }

    constexpr double scaleFactor = 1.15;

    if (event->angleDelta().y() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
        m_currentScale *= scaleFactor;
    } else {
        // Zoom out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        m_currentScale /= scaleFactor;
    }

    emit zoomChanged(static_cast<int>(m_currentScale * 100));
    event->accept();
}

void FSMView::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);

    menu.setStyleSheet(R"(
    QMenu {
        background-color: #333;
        color: white;
        border: 1px solid #555;
        border-radius: 10px;          /* Rounded corners */
        padding: 5px;                 /* Optional padding inside the menu */
    }
    QMenu::item {
        padding: 8px 30px;
        font-size: 14px;
        border-radius: 6px;          /* Rounded hover effect */
    }
    QMenu::item:selected {
        background-color: #555;
    }
)");

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
