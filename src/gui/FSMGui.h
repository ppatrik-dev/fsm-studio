#ifndef FSMGUI_H
#define FSMGUI_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QDebug>
#include <GenericRowWidget.h>

#include "FSMScene.h"

class FSMGui : public QObject
{
    Q_OBJECT
public:
    explicit FSMGui(QObject *parent = nullptr, FSMScene *fsmScene = nullptr)
        : m_graph(fsmScene) {}

private:
    FSMScene *m_graph;
    QString m_name;
    QString m_description;
    QMap<QString, QString> m_inputs;
    QMap<QString, QString> m_outputs;
    QMap<QString, QString> m_variables;

public:
    FSMScene *getGraph() const {
        return m_graph;
    }

    QMap<QString, QString> getInputs() const {
        return m_inputs;
    }

    QMap<QString, QString> getOutputs() const {
        return m_outputs;
    }

    QMap<QString, QString> getVariables() const {
        return m_variables;
    }

public:
    void saveName(QString name) {
        m_name = name;
    }

    void saveInputs(const QList<GenericRowWidget*> &rows);
    void saveOutputs(const QList<GenericRowWidget*> &rows);
    void saveVariables(const QList<GenericRowWidget*> &rows);

signals:
};

#endif // FSMGUI_H
