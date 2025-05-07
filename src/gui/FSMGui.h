#ifndef FSMGUI_H
#define FSMGUI_H

#include "ui_mainwindow.h"
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
    explicit FSMGui(FSMScene *fsmScene)
        : simulationMode(false), m_graph(fsmScene), m_initialState(nullptr) {}

private:
    bool simulationMode;
    FSMScene *m_graph;
    QString m_name;
    QString m_description;
    FSMState *m_initialState;
    QMap<QString, QString> m_inputs;
    QMap<QString, QString> m_outputs;
    QMap<QString, QString> m_variables;

public:
    FSMState *getInitialState() const {
        return m_initialState;
    }

    FSMScene *getGraph() const
    {
        return m_graph;
    }

    QMap<QString, QString> getInputs() const
    {
        return m_inputs;
    }

    QMap<QString, QString> getOutputs() const
    {
        return m_outputs;
    }

    QMap<QString, QString> getVariables() const
    {
        return m_variables;
    }

public:
    void setInitialState(FSMState *state);

    void saveName(QString name)
    {
        m_name = name;
        emit saveNameValue(name);
    }

    void saveDescription(QString info)
    {
        m_description = info;
        emit saveDescriptionValue(info);
    }

    void saveInputs(const QList<GenericRowWidget *> rows);
    void saveOutputs(const QList<GenericRowWidget *> rows);
    void saveVariables(const QList<GenericRowWidget *> rows);

    void deleteInput(const QString &key);
    void deleteOutput(const QString &key);
    void deleteVariable(const QString &key);

    void runSimulation(Ui::MainWindow *ui);
signals:
    void initialStateChanged(FSMState *state);
    void inputAddValue(const QString key, const QString value);
    void inputDeleteValue(const QString key);
    void outputAddValue(const QString key, const QString value);
    void outputDeleteValue(const QString key);
    void variableAddValue(const QString key, const QString value);
    void variableDeleteValue(const QString key);
    void saveNameValue(const QString &name);
    void saveDescriptionValue(const QString &comment);
    void getVarValue(QMap<QString, QString> &automate_backup, const QString &mode); // input output variable
    void getNameValue(QString &name);
    void getDescriptionValue(QString &comment);
    void getStartStateValue(QString &startState);
};

#endif // FSMGUI_H
