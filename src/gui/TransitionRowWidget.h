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

    /// all comments for function in .cpp

    explicit TransitionRowWidget(QWidget *parent = nullptr);
    void setTransitionTexts(const QString &conditionText, const QString &toStateText);
    QString getConditionText() const;
    QString getToStateText() const;
    QTextEdit* getConditionEdit();
    QTextEdit* getToStateEdit();

    void setTransitionItem(FSMTransition *transition) {
        transitionItem = transition;
    }

    FSMTransition* getTransitionItem() const {
        return transitionItem;
    }

    void disableCreateButton() const {
        createButton->setDisabled(true);
    }

signals:
    void requestCreate(TransitionRowWidget *self);
    void requestRemove(TransitionRowWidget *self);
};

#endif // TRANSITIONROWWIDGET_H
