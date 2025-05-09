// File: FSMView.h
// Author: Patrik Prochazka
// Login: xprochp00

#ifndef FSMVIEW_H
#define FSMVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include "FSMScene.h"

class FSMView : public QGraphicsView {
    Q_OBJECT
private:
    double m_currentScale = 1.0;
    QTransform m_savedTransform;
    bool m_transformSaved = false;

public:
    explicit FSMView(QWidget *parent = nullptr);
    void fitToSceneOnce();
    void restorePreviousView();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void wheelEvent(QWheelEvent *event);

signals:
    void zoomChanged(int percent);
    void addStateRequested(const QPointF &pos);
    void addTransitionRequested();
    void deleteStateRequested();
    void deleteTransitionRequested();
};

#endif // FSMVIEW_H
