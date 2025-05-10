/**
 * @file TerminalWidget.cpp
 * @author Filip Ficka, xfickaf00
 * @brief cpp file for functions from TerminalWidget.h
 * @version 1.4
 * @date 2025-05-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "TerminalWidget.h"
#include <QFont>
#include <QScrollBar>
#include <QDateTime>
#include <QScrollArea>

/**
 * @brief Construct a new Terminal Widget:: Terminal Widget object
 * 
 * @param parent widget to bound TerminalWidget to scrollArea
 */
TerminalWidget::TerminalWidget(QWidget *parent)
    : QWidget(parent)
{
    /// creating layout
    this->setStyleSheet("background-color: transparent; border: none;");

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(2);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
}

/**
 * @brief function for comunication with backend part of app
 * printing debug from simulation into this terminal
 * 
 * @param type type of message (ERROR, INFO etc.)
 * @param content message itself
 */
void TerminalWidget::receiveMessage(QString type, QString content) {

    /// setting color for line
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

    /// concate strings
    QString lineText = QString("%1 %2").arg(type, content);
    appendLine(lineText, color);
}

void TerminalWidget::appendLine(const QString &text, int color)
{   
    /// getting time into string
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    /// creating layout
    QWidget *lineWidget = new QWidget();
    QHBoxLayout *lineLayout = new QHBoxLayout(lineWidget);
    lineLayout->setContentsMargins(0, 0, 0, 0);
    lineLayout->setSpacing(10);

    /// creating labels, one for time, second for message
    QLabel *textLabel = new QLabel(text);
    QLabel *timeLabel = new QLabel(timestamp);

    /// setting fonts
    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);
    textLabel->setFont(font);
    timeLabel->setFont(font);

    /// setting color
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
        // purple
        colorStyle = "#8E24AA";
    }

    /// set style
    textLabel->setStyleSheet(QString("color: %1;").arg(colorStyle));
    timeLabel->setStyleSheet("color: gray;");

    /// create whole line widget
    lineLayout->addWidget(textLabel);
    lineLayout->addStretch();
    lineLayout->addWidget(timeLabel);

    layout->addWidget(lineWidget);
    buffer.push_back(lineWidget);

    /// if buffer is full delete oldest line
    if (buffer.size() > maxLines)
        removeOldest();

    this->adjustSize();
    /// send signal to lower scrollArea
    emit lineAppended();
}

/**
 * @brief function to delete oldest line in buffer
 * 
 */
void TerminalWidget::removeOldest()
{
    QWidget *old = buffer.front();
    layout->removeWidget(old);
    buffer.pop_front();
    old->deleteLater();
}

/**
 * @brief function for clearing whole terminal
 * 
 */
void TerminalWidget::clearTerminal()
{
    for (QWidget *line : buffer) {
        layout->removeWidget(line);
        line->deleteLater();
    }
    buffer.clear();
}
