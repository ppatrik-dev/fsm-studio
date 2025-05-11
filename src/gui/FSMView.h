/**
 * @file FSMView.h
 * @author Patrik Prochazka (xprochp00@vutbr.cz)
 * @brief Header file for FSMView class
 * @version 2.0
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef FSMVIEW_H
#define FSMVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include "FSMScene.h"

/**
 * @brief FSMView class, inherit from QGraphicsView
 * 
 */
class FSMView : public QGraphicsView {
    Q_OBJECT
private:
    double m_currentScale = 1.0;
    QTransform m_savedTransform;
    bool m_transformSaved = false;

public:
    /**
     * @brief Construct a new FSMView object
     * 
     * @param parent 
     */
    explicit FSMView(QWidget *parent = nullptr);

    /**
     * @brief Fit scene in simulation
     * 
     */
    void fitToSceneOnce();

    /**
     * @brief Restore previous view before simulation
     * 
     */
    void restorePreviousView();

protected:
    /**
     * @brief Context menu override implementation
     * 
     * @param event 
     */
    void contextMenuEvent(QContextMenuEvent *event) override;

    /**
     * @brief Wheel event action implementation
     * 
     * @param event 
     */
    void wheelEvent(QWheelEvent *event);

signals:
    /**
     * @brief View zoom changed signal
     * 
     * @param percent 
     */
    void zoomChanged(int percent);
    
    /**
     * @brief Request add state signal
     * 
     * @param pos 
     */
    void addStateRequested(const QPointF &pos);

    /**
     * @brief Request add transition signal
     * 
     */
    void addTransitionRequested();

    /**
     * @brief Request delete state signal
     * 
     */
    void deleteStateRequested();

    /**
     * @brief Request delete transition signal
     * 
     */
    void deleteTransitionRequested();
};

#endif // FSMVIEW_H
