/**
 * @file MooreJsClass.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QEventLoop>

/**
 * @brief
 *
 */
class MooreJs : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Moore Js object
     *
     * @param parent
     */
    explicit MooreJs(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

public slots:
    /**
     * @brief
     *
     * @param a
     * @param b
     * @return int
     */
    int multiply(int a, int b)
    {
        return a * b;
    }
    /**
     * @brief
     *
     * @param message
     */
    void print(const QString &message)
    {
        qDebug() << message;
    }
    /**
     * @brief
     *
     * @param timeout
     * @return true
     * @return false
     */
    bool timer(qint32 timeout)
    {
        QEventLoop loop;
        QTimer::singleShot(timeout, &loop, &QEventLoop::quit);
        loop.exec();
        return true;
    }
};
