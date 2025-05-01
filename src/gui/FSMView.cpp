// File: FSMView.cpp
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
    // setContextMenuPolicy(Qt::DefaultContextMenu);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::TextAntialiasing);
}

void FSMView::contextMenuEvent(QContextMenuEvent *event) {
    QMenu contextMenu(this);

    QAction *addStateAction = new QAction("Add State", this);
    // QAction *addTransitionAction = new QAction("Add Transition", this);

    connect(addStateAction, &QAction::triggered, this, [=]() {
        emit addStateRequested(mapToScene(event->pos()));
    });

    // connect(addTransitionAction, &QAction::triggered, this, [=]() {
    //     emit addTransitionRequested();  // Emit transition request
    // });

    contextMenu.addAction(addStateAction);
    // contextMenu.addAction(addTransitionAction);
    contextMenu.exec(event->globalPos());
}
