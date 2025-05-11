// MooreJsClass.h
#pragma once

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QEventLoop>

class MooreJs : public QObject
{
    Q_OBJECT
public:
    explicit MooreJs(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

public slots:
    int multiply(int a, int b)
    {
        return a * b;
    }

    void print(const QString &message)
    {
        qDebug() << message;
    }

    bool timer(qint32 timeout)
    {
        QEventLoop loop;
        QTimer::singleShot(timeout, &loop, &QEventLoop::quit);
        loop.exec();
        return true;
    }
};
