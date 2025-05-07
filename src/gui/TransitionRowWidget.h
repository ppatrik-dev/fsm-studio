#ifndef TRANSITIONROWWIDGET_H
#define TRANSITIONROWWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "FSMTransition.h"

class QTextEdit;
class QPushButton;

class FSMTransition;

class TransitionRowWidget : public QWidget
{
    Q_OBJECT

private:
    QTextEdit *conditionEdit;
    QTextEdit *toStateEdit;
    QPushButton *createButton;
    QPushButton *removeButton;

    FSMTransition *transitionItem;

public:
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
