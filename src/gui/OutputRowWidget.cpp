#include "OutputRowWidget.h"

OutputRowWidget::OutputRowWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QLineEdit *key = new QLineEdit("A");
    QLineEdit *value = new QLineEdit("1");
    QPushButton *removeButton = new QPushButton("🗑");

    layout->addWidget(key);
    layout->addWidget(value);
    layout->addWidget(removeButton);

    connect(removeButton, &QPushButton::clicked, this, [=]() {
        emit requestDelete(this);
    });
}
