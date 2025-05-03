#ifndef CONDITIONROWWIDGET_H
#define CONDITIONROWWIDGET_H

#include <QWidget>

class QTextEdit;
class QPushButton;

class ConditionRowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConditionRowWidget(QWidget *parent = nullptr);

signals:
    void requestDelete(ConditionRowWidget *self);

private:
    QTextEdit *ifEdit;
    QTextEdit *thenEdit;
    QPushButton *deleteButton;
};

#endif // CONDITIONROWWIDGET_H
