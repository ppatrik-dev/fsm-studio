/**
 * @file TransitionRowWidget.h
 * @author Filip Ficka, xfickaf00
 * @brief header file for TransitionRowWidget object
 * @version 1.2
 * @date 2025-05-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TRANSITIONROWWIDGET_H
#define TRANSITIONROWWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "FSMTransition.h"

class QTextEdit;
class QPushButton;
class FSMTransition;

/**
 * @brief TransitionRowWidget class, inheretance from QWidget
 * 
 */
class TransitionRowWidget : public QWidget
{
    Q_OBJECT

private:

    /// pointers to widget child objects, pointer to actuall FSMTransition

    QTextEdit *conditionEdit;
    QTextEdit *toStateEdit;
    QPushButton *createButton;
    QPushButton *removeButton;

    FSMTransition *transitionItem;

public:

    /**
     * @brief Construct a new Transition Row Widget:: Transition Row Widget object
     * 
     * @param parent widget to bound TransitionRow row
     */
    explicit TransitionRowWidget(QWidget *parent = nullptr);

    /**
     * @brief function to set conditionText, toStateTxt
     * 
     * @param conditionText 
     * @param toStateText 
     */
    void setTransitionTexts(const QString &conditionText, const QString &toStateText);

    /**
     * @brief function to get condition
     * 
     * @return QTextEdit* 
     */
    QString getConditionText() const;

    /**
     * @brief function to get state
     * 
     * @return QTextEdit* 
     */
    QString getToStateText() const;

    /**
     * @brief function to get conditionEdit widget
     * 
     * @return QTextEdit* 
     */
    QTextEdit* getConditionEdit();

    /**
     * @brief function to get conditionEdit widget
     * 
     * @return QTextEdit* 
     */
    QTextEdit* getToStateEdit();

    /**
     * @brief Set the Transition Item object
     * 
     * @param transition 
     */
    void setTransitionItem(FSMTransition *transition) {
        transitionItem = transition;
    }

    /**
     * @brief Get the Transition Item object
     * 
     * @return FSMTransition* 
     */
    FSMTransition* getTransitionItem() const {
        return transitionItem;
    }

    /**
     * @brief function to disable the create button
     */
    void disableCreateButton(QString style) const;

signals:
    void requestCreate(TransitionRowWidget *self);
    void requestRemove(TransitionRowWidget *self);
};

#endif // TRANSITIONROWWIDGET_H
