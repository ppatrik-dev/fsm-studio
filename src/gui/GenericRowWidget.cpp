// File: GenericRowWidget.cpp
// Author: Filip Ficka
// Login: xfickaf00


#include "GenericRowWidget.h"

GenericRowWidget::GenericRowWidget(RowType type, QWidget *parent)
    : QWidget(parent), rowType(type)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    keyEdit = new QLineEdit(this);
    valueEdit = new QLineEdit(this);
    QPushButton *deleteButton = new QPushButton("D", this);
    deleteButton->setFixedSize(35, 30);

    layout->addWidget(keyEdit);
    layout->addWidget(valueEdit);
    layout->addWidget(deleteButton);

    // switch for data depending on type
    switch (type) {
    case Input:
        keyEdit->setText("InputKey");
        valueEdit->setText("1");
        break;
    case Output:
        keyEdit->setText("OutputKey");
        valueEdit->setText("0");
        break;
    case Variable:
        keyEdit->setText("VarKey");
        valueEdit->setText("100");
        break;
    }

    connect(deleteButton, &QPushButton::clicked, this, [=]() {
        emit requestDelete(this);
    });
}

QString GenericRowWidget::key() const {
    return keyEdit->text();
}

QString GenericRowWidget::value() const {
    return valueEdit->text();
}
