// File: GenericRowWidget.h
// Author: Filip Ficka
// Login: xfickaf00

#ifndef GENERICROWWIDGET_H
#define GENERICROWWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class GenericRowWidget : public QWidget
{
    Q_OBJECT

public:
    enum RowType { Input, Output, Variable };

    explicit GenericRowWidget(RowType type, QWidget *parent = nullptr);
    void setGenericTexts(const QString &keyText, const QString &valueText);
    void disableKeyEdit();
    QString key() const;
    QString value() const;
    void setDeleteButtonEnabled(bool enabled);

signals:
    void requestDelete(GenericRowWidget *self);

private:
    QLineEdit *keyEdit;
    QLineEdit *valueEdit;
    RowType rowType;
    QPushButton *deleteButton;
};

#endif // GENERICROWWIDGET_H
