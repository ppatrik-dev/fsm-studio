/**
 * @file GenericRowWidget.cpp
 * @author Filip Ficka, xfickaf00
 * @brief cpp file for functions from GenericRowWidget.h
 * @version 1.2
 * @date 2025-05-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "GenericRowWidget.h"

GenericRowWidget::GenericRowWidget(RowType type, QWidget *parent)
    : QWidget(parent), rowType(type)
{   
    /// create new box layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    /// create button, lineEdits
    keyEdit = new QLineEdit(this);
    valueEdit = new QLineEdit(this);
    deleteButton = new QPushButton("D", this);
    deleteButton->setFixedSize(35, 30);

    /// append it
    layout->addWidget(keyEdit);
    layout->addWidget(valueEdit);
    layout->addWidget(deleteButton);

    /// set initial strings
    keyEdit->setPlaceholderText("name");
    valueEdit->setPlaceholderText("value");

    /// connect delete button
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

QString GenericRowWidget::getKey() const {
    return keyEdit->text();
}

QString GenericRowWidget::getValue() const {
    return valueEdit->text();
}

void GenericRowWidget::setValue(QString value) {
    valueEdit->setText(value);
}

void GenericRowWidget::setDeleteButtonEnabled(bool enabled)
{
    if (deleteButton){

        deleteButton->setEnabled(enabled);

        if (!enabled){
            deleteButton->setStyleSheet(disableStyle);
        }

        else {
            deleteButton->setStyleSheet("");
        }
    }
}
