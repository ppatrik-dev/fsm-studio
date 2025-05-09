#include "TerminalWidget.h"
#include <QFont>
#include <QScrollBar>
#include <QScrollArea>

TerminalWidget::TerminalWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet("background-color: transparent; border: none;");

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(2);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

void TerminalWidget::receiveMessage(QString type, QString content) {
}

void TerminalWidget::appendLine(const QString &text, int color)
{
    QString lineText = QString::asprintf(">>> %s", text.toUtf8().constData());
    QLabel *line = new QLabel(lineText);
    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);
    line->setFont(font);
    line->setStyleSheet(R"(
        QLabel {
            background-color: transparent;
            color: #BA68C8;
            border: none;
            padding: 2px 6px;
            margin-bottom: 2px;
        }
    )");

    if (color == 0){
        line->setStyleSheet("color: white;");
    }
    else if (color == 1){
        line->setStyleSheet("color: #8BC34A;"); // green
    }
    else if (color == 2){
        line->setStyleSheet("color: #E57373;"); // red
    }
    else if (color == 3){
        line->setStyleSheet("color: #64B5F6"); // blue
    }
    else if (color == 4){
        line->setStyleSheet("color: #FFD54F"); // yellow
    }
    else{
        line->setStyleSheet("color: #8E24AA"); // purple
    }

    layout->addWidget(line);
    buffer.push_back(line);

    if (buffer.size() > maxLines)
        removeOldest();

    emit lineAppended();
}

void TerminalWidget::removeOldest()
{
    QLabel *old = buffer.front();
    layout->removeWidget(old);
    buffer.pop_front();
    old->deleteLater();
}

void TerminalWidget::clearTerminal()
{
    for (QLabel *line : buffer) {
        layout->removeWidget(line);
        line->deleteLater();
    }
    buffer.clear();
}
