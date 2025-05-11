/**
 * @file FSMView.cpp
 * @author Patrik Prochazka (xprochp00@vutbr.cz)
 * @brief Source file for FSMView class
 * @version 2.0
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "FSMView.h"
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QGraphicsScene>
#include <QContextMenuEvent>
#include <QApplication>

/**
 * @details
 * Construct FSMView object and set some flags
 */
FSMView::FSMView(QWidget *parent) : QGraphicsView(parent) {
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::TextAntialiasing);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

/**
 * @details 
 * Define mouse wheel event zooming
 */
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

/**
 * @details
 * Handles right click scene menu with option to edit the FSM
 */
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

    QAction *selected = menu.exec(event->globalPos());

    if (selected == addStateAction) {
        emit addStateRequested(mapToScene(event->pos()));
    } else if (selected == addTransitionAction) {
        emit addTransitionRequested();
    } else if (selected == deleteStateAction) {
        emit deleteStateRequested();
    }
}

/**
 * @details
 * Fitting view to window
 */
void FSMView::fitToSceneOnce()
{
    if (!scene()) return;

    if (!m_transformSaved) {
        m_savedTransform = transform();
        m_transformSaved = true;
    }

    QRectF bounds = scene()->itemsBoundingRect();
    if (!bounds.isNull()) {
        fitInView(bounds, Qt::KeepAspectRatio);
    }
}

/**
 * @details
 * Restoring previous view
 */
void FSMView::restorePreviousView()
{
    if (m_transformSaved) {
        setTransform(m_savedTransform);
        m_transformSaved = false;
    }
}
