#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QScrollArea>
#include <deque>

class TerminalWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TerminalWidget(QWidget *parent = nullptr);
    void appendLine(const QString &text, int color = 0);
    void clearTerminal();

private:
    QVBoxLayout *layout;
    std::deque<QLabel*> buffer;
    const unsigned int maxLines = 150;

    void removeOldest();

public slots:
    void receiveMessage(QString type, QString content);

signals:
    void lineAppended();
};

#endif // TERMINALWIDGET_H
