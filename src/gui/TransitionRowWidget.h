#ifndef TRANSITIONROWWIDGET_H
#define TRANSITIONROWWIDGET_H

#include <QWidget>

class QTextEdit;
class QPushButton;

class TransitionRowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransitionRowWidget(QWidget *parent = nullptr);
    void setTransitionTexts(const QString &conditionText, const QString &toStateText);
    QString getConditionText() const;
    QString getToStateText() const;
    QTextEdit* getConditionEdit();
    QTextEdit* getToStateEdit();

signals:
    void requestDelete(TransitionRowWidget *self);

private:
    QTextEdit *conditionEdit;
    QTextEdit *toStateEdit;
    QPushButton *deleteButton;
};

#endif // TRANSITIONROWWIDGET_H
