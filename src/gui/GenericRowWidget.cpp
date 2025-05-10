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

/**
 * @brief Construct a new Generic Row Widget:: Generic Row Widget object
 * 
 * @param type setting type from enum decleared in header file
 * @param parent widget to bound generic row
 */
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

/**
 * @brief function for diseabling name rewrite
 * 
 */
void GenericRowWidget::disableKeyEdit() {
    keyEdit->setReadOnly(true);
}

/**
 * @brief function for setting text into genericRow
 * 
 * @param keyText name of row
 * @param valueText value that it contains
 */
void GenericRowWidget::setGenericTexts(const QString &keyText, const QString &valueText) {
    keyEdit->setText(keyText);
    valueEdit->setText(valueText);
}

/**
 * @brief function to get name of row
 * 
 * @return QString 
 */
QString GenericRowWidget::key() const {
    return keyEdit->text();
}

/**
 * @brief function to get value of row
 * 
 * @return QString 
 */
QString GenericRowWidget::value() const {
    return valueEdit->text();
}

/**
 * @brief function to eneable/disable delete button of row
 * 
 * @param enabled 
 */
void GenericRowWidget::setDeleteButtonEnabled(bool enabled)
{
    if (deleteButton)
        deleteButton->setEnabled(enabled);
}
