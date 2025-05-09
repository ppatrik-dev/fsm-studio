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
    deleteButton = new QPushButton("D", this);
    deleteButton->setFixedSize(35, 30);

    layout->addWidget(keyEdit);
    layout->addWidget(valueEdit);
    layout->addWidget(deleteButton);

    // switch for data depending on type
    keyEdit->setPlaceholderText("name");
    valueEdit->setPlaceholderText("value");

    connect(deleteButton, &QPushButton::clicked, this, [=]() {
        emit requestDelete(this);
    });
}

void GenericRowWidget::disableKeyEdit() {
    keyEdit->setReadOnly(true);
}

void GenericRowWidget::setGenericTexts(const QString &keyText, const QString &valueText) {
    keyEdit->setText(keyText);
    valueEdit->setText(valueText);
}

QString GenericRowWidget::key() const {
    return keyEdit->text();
}

QString GenericRowWidget::value() const {
    return valueEdit->text();
}

void GenericRowWidget::setDeleteButtonEnabled(bool enabled)
{
    if (deleteButton)
        deleteButton->setEnabled(enabled);
}
