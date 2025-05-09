#include "TerminalWidget.h"
#include <QFont>
#include <QScrollBar>
#include <QDateTime>
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

    int color = WHITE;
    if (type == "[ERROR]"){
        color = RED;
    }
    if (type == "[INFO]"){
        color = BLUE;
    }
    if (type == "[TRANSITION]"){
        color = GREEN;
    }
    if (type == "[VARIABLE]"){
        color = YELLOW;
    }
    if (type == "[EVALUATE]"){
        color = WHITE;
    }

    QString lineText = QString("%1 %2").arg(type, content);
    appendLine(lineText, color);
}

void TerminalWidget::appendLine(const QString &text, int color)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    QWidget *lineWidget = new QWidget();
    QHBoxLayout *lineLayout = new QHBoxLayout(lineWidget);
    lineLayout->setContentsMargins(0, 0, 0, 0); // žiadne okraje
    lineLayout->setSpacing(10); // medzera medzi textom a časom

    QLabel *textLabel = new QLabel(text);
    QLabel *timeLabel = new QLabel(timestamp);

    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);
    textLabel->setFont(font);
    timeLabel->setFont(font);

    // Nastavenie farby podľa parametra
    QString colorStyle;
    if (color == WHITE){
        colorStyle = "white";
    }
    else if (color == GREEN){
        colorStyle = "#8BC34A";
    }
    else if (color == RED){
        colorStyle = "#E57373";
    }
    else if (color == BLUE){
        colorStyle = "#64B5F6";
    }
    else if (color == YELLOW){
        colorStyle = "#FFD54F";
    }
    else{
        colorStyle = "#8E24AA"; // default - fialová
    }

    textLabel->setStyleSheet(QString("color: %1;").arg(colorStyle));
    timeLabel->setStyleSheet("color: gray;"); // čas menší, šedý

    lineLayout->addWidget(textLabel);
    lineLayout->addStretch(); // natiahne voľné miesto medzi textom a časom
    lineLayout->addWidget(timeLabel);

    layout->addWidget(lineWidget);
    buffer.push_back(lineWidget);

    if (buffer.size() > maxLines)
        removeOldest();

    emit lineAppended();
}

void TerminalWidget::removeOldest()
{
    QWidget *old = buffer.front();
    layout->removeWidget(old);
    buffer.pop_front();
    old->deleteLater();
}

void TerminalWidget::clearTerminal()
{
    for (QWidget *line : buffer) {
        layout->removeWidget(line);
        line->deleteLater();
    }
    buffer.clear();
}
