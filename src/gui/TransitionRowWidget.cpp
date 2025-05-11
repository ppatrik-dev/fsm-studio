/**
 * @file TransitionRowWidget.cpp
 * @author Filip Ficka, xfickaf00
 * @brief cpp file for functions from TransitionRowWidget.h
 * @version 1.2
 * @date 2025-05-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "TransitionRowWidget.h"
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

/**
 * @brief Construct a new Transition Row Widget:: Transition Row Widget object
 * 
 * @param parent widget to bound TransitionRow row
 */
TransitionRowWidget::TransitionRowWidget(QWidget *parent)
    : QWidget(parent), transitionItem(nullptr)
{
    setFixedHeight(380);

    /// creating frame style
    auto *frame = new QFrame(this);
    frame->setObjectName("conditionFrame");
    frame->setFrameShape(QFrame::NoFrame);
    frame->setStyleSheet(R"(
        #conditionFrame {
            border: 2px solid #666;
            border-radius: 12px;
            background-color: #2b2b2b;
        }
    )");

    /// layout for frame
    auto *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(10, 10, 10, 10);
    frameLayout->setSpacing(2);

    QFont font("Fira Code", 12);

    /// IF label
    auto *conditionLabel = new QLabel("Condition", frame);
    conditionLabel->setStyleSheet("background: transparent; border: none; font-weight: bold; font-size: 12pt;");
    conditionLabel->setFixedHeight(30);
    frameLayout->addWidget(conditionLabel);

    /// IF input
    conditionEdit = new QTextEdit(frame);
    conditionEdit->setFont(font);
    frameLayout->addWidget(conditionEdit);

    /// THEN label
    auto *toStateLabel = new QLabel("To", frame);
    toStateLabel->setStyleSheet("background: transparent; border: none; font-weight: bold; font-size: 12pt;");
    toStateLabel->setFixedHeight(30);;
    frameLayout->addWidget(toStateLabel);

    /// THEN input
    toStateEdit = new QTextEdit(frame);
    toStateEdit->setFixedHeight(100);
    toStateEdit->setFont(font);
    frameLayout->addWidget(toStateEdit);

    auto *bottomLayout = new QHBoxLayout();
    bottomLayout->setContentsMargins(0, 10, 0, 0);
    bottomLayout->setSpacing(10);

    /// Create button
    createButton = new QPushButton("Create", frame);
    bottomLayout->addWidget(createButton);

    connect(createButton, &QPushButton::clicked, this, [=](){
        emit requestCreate(this);
    });

    /// Remove button
    removeButton = new QPushButton("Remove", frame);
    bottomLayout->addWidget(removeButton);

    frameLayout->addLayout(bottomLayout);

    /// connecting remove button
    connect(removeButton, &QPushButton::clicked, this, [=]() {
        emit requestRemove(this);
    });

    /// put in frame
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(frame);
}

/**
 * @brief function to set conditionText, toStateTxt
 * 
 * @param conditionText 
 * @param toStateText 
 */
void TransitionRowWidget::setTransitionTexts(const QString &conditionText, const QString &toStateText) {
    conditionEdit->setPlainText(conditionText);
    toStateEdit->setPlainText(toStateText);
}

/**
 * @brief function to get conditionEdit widget
 * 
 * @return QTextEdit* 
 */
QTextEdit* TransitionRowWidget::getConditionEdit() {
    return conditionEdit;
}

/**
 * @brief function to get stateEdit widget
 * 
 * @return QTextEdit* 
 */
QTextEdit* TransitionRowWidget::getToStateEdit() {
    return toStateEdit;
}

/**
 * @brief function to get condition
 * 
 * @return QTextEdit* 
 */
QString TransitionRowWidget::getConditionText() const {
    return conditionEdit->toPlainText();
}

/**
 * @brief function to get state
 * 
 * @return QTextEdit* 
 */
QString TransitionRowWidget::getToStateText() const {
    return toStateEdit->toPlainText();
}

/**
 * @brief function to disable the create button
 */
void TransitionRowWidget::disableCreateButton(QString style) const {
    createButton->setDisabled(true);
    createButton->setStyleSheet(style);
}