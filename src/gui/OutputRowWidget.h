#ifndef OUTPUTROWWIDGET_H
#define OUTPUTROWWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class OutputRowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OutputRowWidget(QWidget *parent = nullptr);

signals:
    void requestDelete(OutputRowWidget *self);
};

#endif // OUTPUTROWWIDGET_H
