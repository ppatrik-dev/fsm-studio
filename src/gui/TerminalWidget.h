/**
 * @file TerminalWidget.h
 * @author Filip Ficka, xfickaf00
 * @brief header file for Terminal object
 * @version 1.4
 * @date 2025-05-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QScrollArea>
#include <deque>

/**
 * @brief enum for color types of line in terminal
 * 
 */
enum COLORS{
    WHITE,
    GREEN,
    RED,
    BLUE,
    YELLOW,
    PURPLE
};

/**
 * @brief TerminalWidget class, inheretance from QWidget
 * 
 */
class TerminalWidget : public QWidget
{
    Q_OBJECT

public:

    /// all comments for function in .cpp

    explicit TerminalWidget(QWidget *parent = nullptr);
    void appendLine(const QString &text, int color = 0);
    void clearTerminal();

private:

    /// pointer for terminal layout, buffer que, const for maxLines in terminal
    QVBoxLayout *layout;
    std::deque<QWidget*> buffer;
    const unsigned int maxLines = 150;

    /**
     * @brief private function for clearing buffer
     * 
     */
    void removeOldest();

public slots:
    void receiveMessage(QString type, QString content);

signals:
    void lineAppended();
};

#endif // TERMINALWIDGET_H
