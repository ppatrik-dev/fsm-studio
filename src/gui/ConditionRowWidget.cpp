#include "ConditionRowWidget.h"
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

ConditionRowWidget::ConditionRowWidget(QWidget *parent)
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

    // IF label
    auto *ifLabel = new QLabel("IF", frame);
    ifLabel->setStyleSheet("background: transparent; border: none; font-weight: bold; font-size: 12pt;");
    ifLabel->setFixedHeight(30);
    frameLayout->addWidget(ifLabel);

    // IF input
    ifEdit = new QTextEdit(frame);
    ifEdit->setFixedHeight(100);
    frameLayout->addWidget(ifEdit);

    // THEN label
    auto *thenLabel = new QLabel("Then", frame);
    thenLabel->setStyleSheet("background: transparent; border: none; font-weight: bold; font-size: 12pt;");
    thenLabel->setFixedHeight(30);
    frameLayout->addWidget(thenLabel);

    // THEN input
    thenEdit = new QTextEdit(frame);
    thenEdit->setFixedHeight(100);
    frameLayout->addWidget(thenEdit);

    // delete button aligned right
    deleteButton = new QPushButton("Delete", frame);
    auto *bottomLayout = new QHBoxLayout();
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

void ConditionRowWidget::setConditionTexts(const QString &ifText, const QString &thenText) {
    ifEdit->setPlainText(ifText);
    thenEdit->setPlainText(thenText);
}

QString ConditionRowWidget::getIfText() const {
    return ifEdit->toPlainText();
}

QString ConditionRowWidget::getThenText() const {
    return thenEdit->toPlainText();
}
