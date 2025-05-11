/**
 * @file FSMGui.h
 * @author Patrik Prochazka, xprochp00, Miroslav Basista (xbasism00@vutbr.cz)
 * @brief Header file for FSM Gui class
 * @version 2.0
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef FSMGUI_H
#define FSMGUI_H

#include "ui_mainwindow.h"
#include <QObject>
#include <QMap>
#include <QString>
#include <QDebug>
#include <GenericRowWidget.h>

#include "FSMScene.h"

/**
 * @brief FSMGui class, inherit from QObject
 *
 */
class FSMGui : public QObject
{
    Q_OBJECT

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
    /**
     * @brief Construct a new FSMGui object
     *
     * @param fsmScene
     */
    explicit FSMGui(FSMScene *fsmScene)
        : simulationMode(false), m_graph(fsmScene), m_initialState(nullptr) {}

    /**
     * @brief Get the Initial State object
     *
     * @return FSMState*
     */
    FSMState *getInitialState() const
    {
        return m_initialState;
    }

    /**
     * @brief Get the Graph object
     *
     * @return FSMScene*
     */
    FSMScene *getGraph() const
    {
        return m_graph;
    }

    /**
     * @brief Get the Name object
     *
     * @return QString
     */
    QString getName() const
    {
        return m_name;
    }

    /**
     * @brief Get the Description object
     *
     * @return QString
     */
    QString getDescription() const
    {
        return m_description;
    }

    /**
     * @brief Get the Inputs object
     *
     * @return QMap<QString, QString>
     */
    QMap<QString, QString> getInputs() const
    {
        return m_inputs;
    }

    /**
     * @brief Get the Outputs object
     *
     * @return QMap<QString, QString>
     */
    QMap<QString, QString> getOutputs() const
    {
        return m_outputs;
    }

    /**
     * @brief Get the Variables object
     *
     * @return QMap<QString, QString>
     */
    QMap<QString, QString> getVariables() const
    {
        return m_variables;
    }

public:
    /**
     * @brief Set the Initial State object
     *
     * @param state
     */
    void setInitialState(FSMState *state);

    /**
     * @brief Save FSM name
     *
     * @param name
     */
    void saveName(QString name)
    {
        m_name = name;
        emit saveNameValue(name);
    }

    /**
     * @brief save FSM description
     *
     * @param info
     */
    void saveDescription(QString info)
    {
        m_description = info;
        emit saveDescriptionValue(info);
    }

    /**
     * @brief Save FSM inputs
     *
     * @param rows
     */
    void saveInputs(const QList<GenericRowWidget *> rows);

    /**
     * @brief Save FSM outputs
     *
     * @param rows
     */
    void saveOutputs(const QList<GenericRowWidget *> rows);

    /**
     * @brief Save FSM variables
     *
     * @param rows
     */
    void saveVariables(const QList<GenericRowWidget *> rows);

    /**
     * @brief Delete FSM input
     *
     * @param key
     */
    void deleteInput(const QString &key);

    /**
     * @brief Delete FSM output
     *
     * @param key
     */
    void deleteOutput(const QString &key);

    /**
     * @brief Delete FSM variable
     *
     * @param key
     */
    void deleteVariable(const QString &key);

signals:
    /**
     * @brief Initial state changed signal
     *
     * @param stateLabel
     */
    void initialStateChanged(QString stateLabel);

    /**
     * @brief New variable added signal
     *
     * @param key
     * @param value
     */
    void inputAddValue(const QString key, const QString value);

    /**
     * @brief Variable deleted signal
     *
     * @param key
     */
    void inputDeleteValue(const QString key);

    /**
     * @brief New output added signal
     *
     * @param key
     * @param value
     */
    void outputAddValue(const QString key, const QString value);

    /**
     * @brief Output deleted signal
     *
     * @param key
     */
    void outputDeleteValue(const QString key);

    /**
     * @brief New variable added signal
     *
     * @param key
     * @param value
     */
    void variableAddValue(const QString key, const QString value);

    /**
     * @brief Variable deleted signal
     *
     * @param key
     */
    void variableDeleteValue(const QString key);

    /**
     * @brief Save FSM name signal
     *
     * @param name
     */
    void saveNameValue(QString name);

    /**
     * @brief Save FSM description value
     *
     * @param comment
     */
    void saveDescriptionValue(QString comment);

    /**
     * @brief Get FSM details signal
     *
     * @param automate_backup
     * @param mode
     */
    void getVarValue(QMap<QString, QString> &automate_backup, const QString &mode);

    /**
     * @brief Get FSM name signal
     *
     * @param name
     */
    void getNameValue(QString &name);

    /**
     * @brief Get the FSM description signal
     *
     * @param comment
     */
    void getDescriptionValue(QString &comment);

    /**
     * @brief Get start state signal
     *
     * @param startState
     */
    void getStartStateValue(QString &startState);

    /**
     * @brief Display FSM details signal
     *
     */
    void displayDetailsRequested();

    /**
     * @brief Display updated input signal
     *
     * @param key
     * @param value
     */
    void displayUpdatedInputRequested(QString key, QString value);

    /**
     * @brief Display updated output signal
     *
     * @param key
     * @param value
     */
    void displayUpdatedOutputRequested(QString key, QString value);

    /**
     * @brief Display updated variable signal
     *
     * @param key
     * @param value
     */
    void displayUpdatedVariableRequested(QString key, QString value);

public slots:
    /**
     * @brief Save imported FSM details
     *
     */
    void importDetails();

    /**
     * @brief Save updated input value
     *
     * @param key
     * @param value
     */
    void updateInput(QString key, QString value);

    /**
     * @brief Save updated output value
     *
     * @param key
     * @param value
     */
    void updateOutput(QString key, QString value);

    /**
     * @brief Save updated variable value
     *
     * @param key
     * @param value
     */
    void updateVariable(QString key, QString value);
};

#endif // FSMGUI_H
