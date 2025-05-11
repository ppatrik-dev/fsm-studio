/**
 * @file MooreJsClass.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Provides a QObject-derived helper class for use in QJSEngine scripting
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
 * @class MooreJs
 * @brief Helper QObject for exposing utility functions to QJSEngine
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
     * @brief Custom function for multiply in the QJSEngine
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
     * @brief Custom function for print in the QJSEngine
     *
     * @param message
     */
    void print(const QString &message)
    {
        qDebug() << message;
    }
    /**
     * @brief Custom function for timeout in the QJSEngine
     *
     * @param timeout
     * @return true
     * @return false
     */
    bool timer(qint32 timeout)
    {
        /// @brief Waits for a specified timeout duration
        QEventLoop loop;
        QTimer::singleShot(timeout, &loop, &QEventLoop::quit);
        loop.exec();
        return true;
    }
};
