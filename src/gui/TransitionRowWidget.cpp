#include "TransitionRowWidget.h"
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

TransitionRowWidget::TransitionRowWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(380);

    // creating frame style
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

    // layout for frame
    auto *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(10, 10, 10, 10);
    frameLayout->setSpacing(2);

    QFont font("Fira Code", 12);

    // IF label
    auto *conditionLabel = new QLabel("Condition", frame);
    conditionLabel->setStyleSheet("background: transparent; border: none; font-weight: bold; font-size: 12pt;");
    conditionLabel->setFixedHeight(30);
    frameLayout->addWidget(conditionLabel);

    // IF input
    conditionEdit = new QTextEdit(frame);
    conditionEdit->setFont(font);
    frameLayout->addWidget(conditionEdit);

    // THEN label
    auto *toStateLabel = new QLabel("To", frame);
    toStateLabel->setStyleSheet("background: transparent; border: none; font-weight: bold; font-size: 12pt;");
    toStateLabel->setFixedHeight(30);;
    frameLayout->addWidget(toStateLabel);

    // THEN input
    toStateEdit = new QTextEdit(frame);
    toStateEdit->setFixedHeight(100);
    toStateEdit->setFont(font);
    frameLayout->addWidget(toStateEdit);

    // delete button aligned right
    deleteButton = new QPushButton("Delete", frame);
    auto *bottomLayout = new QHBoxLayout();
    bottomLayout->setContentsMargins(0, 10, 0, 0);
    bottomLayout->addStretch();
    bottomLayout->addWidget(deleteButton);
    frameLayout->addLayout(bottomLayout);

    connect(deleteButton, &QPushButton::clicked, this, [=]() {
        emit requestDelete(this);
    });

    // put in frame
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(frame);
}

void TransitionRowWidget::setTransitionTexts(const QString &conditionText, const QString &toStateText) {
    conditionEdit->setPlainText(conditionText);
    toStateEdit->setPlainText(toStateText);
}

QTextEdit* TransitionRowWidget::getConditionEdit() {
    return conditionEdit;
}

QTextEdit* TransitionRowWidget::getToStateEdit() {
    return toStateEdit;
}

QString TransitionRowWidget::getConditionText() const {
    return conditionEdit->toPlainText();
}

QString TransitionRowWidget::getToStateText() const {
    return toStateEdit->toPlainText();
}
