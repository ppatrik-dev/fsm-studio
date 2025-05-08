// MooreJsClass.h
#pragma once

#include <QObject>
#include <QDebug>

class MooreJs : public QObject
{
    Q_OBJECT
public slots:
    int multiply(int a, int b)
    {
        return a * b;
    }
    void print(const QString &message)
    {
        qDebug() << message;
    }
    void timer(qint32 timeout)
    {
        emit stepTimeout(timeout);
    }
signals:
    void stepTimeout(qint32 timeout);
};
