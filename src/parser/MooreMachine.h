/**
 * @file MooreMachine.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QObject>
#include <memory>
#include "MooreState.h"
#include <QRegularExpression>

/**
 * @brief
 *
 */
class MooreMachine : public QObject
{
    Q_OBJECT

    QString automate_name;
    QString automate_comment;
    QString start_state;
    QMap<QString, QString> automate_inputs;
    QMap<QString, QString> automate_outputs;
    QMap<QString, QString> variables;

public:
    /// @brief
    QMap<QString, std::shared_ptr<MooreState>> states;
    /**
     * @brief Construct a new Moore Machine object
     *
     * @param parent
     */
    explicit MooreMachine(QObject *parent = nullptr);
    /**
     * @brief Construct a new Moore Machine object
     *
     * @param name
     * @param comment
     * @param parent
     */
    MooreMachine(const QString &name, const QString &comment, QObject *parent = nullptr);
    /**
     * @brief Destroy the Moore Machine object
     *
     */
    ~MooreMachine() override;
    /**
     * @brief
     *
     * @param name
     */
    void addInputs(const QString &name);
    /**
     * @brief
     *
     * @param name
     */
    void addOutputs(const QString &name);
    /**
     * @brief
     *
     * @param command
     */
    void addVariable(const QString &command);
    /**
     * @brief Get the Name object
     *
     * @return const QString&
     */
    const QString &getName() const;
    /**
     * @brief Get the Comment object
     *
     * @return const QString&
     */
    const QString &getComment() const;
    /**
     * @brief Get the Start State object
     *
     * @return const QString&
     */
    const QString &getStartState() const;
    /**
     * @brief Get the Inputs object
     *
     * @return QVector<QString>
     */
    QVector<QString> getInputs() const;
    /**
     * @brief Get the Map Inputs object
     *
     * @return QMap<QString, QString>
     */
    QMap<QString, QString> getMapInputs() const;
    /**
     * @brief Get the Outputs object
     *
     * @return QVector<QString>
     */
    QVector<QString> getOutputs() const;
    /**
     * @brief Get the Variables object
     *
     * @return QVector<QString>
     */
    QVector<QString> getVariables() const;
    /**
     * @brief Create a Var Command object
     *
     * @param name
     * @param value
     * @return QString
     */
    QString createVarCommand(const QString &name, const QString &value);
    /**
     * @brief Create a Dynamic Var Command object
     *
     * @param name
     * @param value
     * @return QString
     */
    QString createDynamicVarCommand(const QString &name, const QString &value);
    /**
     * @brief
     *
     * @param command
     * @return QString
     */
    QString extractVariableName(const QString &command);
    /**
     * @brief
     *
     * @param command
     * @return QString
     */
    QString extractVariableValue(const QString &command);
    /**
     * @brief
     *
     * @param name
     * @param state
     */
    void addState(const QString &name, const std::shared_ptr<MooreState> &state);
    /**
     * @brief Get the State object
     *
     * @param name
     * @return std::shared_ptr<MooreState>
     */
    std::shared_ptr<MooreState> getState(const QString &name);

public slots:
    /**
     * @brief Create a And Add State object
     *
     * @param state
     * @param stateName
     * @param output
     */
    void createAndAddState(std::shared_ptr<MooreState> &state, const QString &stateName, const QString &output);
    /**
     * @brief Create a Transition object
     *
     * @param state
     * @param action
     * @param targetStateName
     */
    void createTransition(const std::shared_ptr<MooreState> &state, const QString &action, const QString &targetStateName);
    /**
     * @brief Set the Name object
     *
     * @param name
     */
    void setName(QString name);
    /**
     * @brief Set the Comment object
     *
     * @param comment
     */
    void setComment(QString comment);
    /**
     * @brief Set the Start State object
     *
     * @param name
     */
    void setStartState(QString name);
    /**
     * @brief
     *
     * @param name
     * @param value
     */
    void addGuiInput(const QString &name, const QString &value);
    /**
     * @brief
     *
     * @param name
     */
    void deleteGuiInput(const QString &name);
    /**
     * @brief
     *
     * @param name
     * @param value
     */
    void addGuiOutput(const QString &name, const QString &value);
    /**
     * @brief
     *
     * @param name
     */
    void deleteGuiOutput(const QString &name);
    /**
     * @brief
     *
     * @param name
     * @param value
     */
    void addGuiVariable(const QString &name, const QString &value);
    /**
     * @brief
     *
     * @param name
     */
    void deleteGuiVariable(const QString &name);
    /**
     * @brief Get the Gui Map object
     *
     * @param automate_backup
     * @param mode
     */
    void getGuiMap(QMap<QString, QString> &automate_backup, const QString &mode);
    /**
     * @brief Get the Gui Name object
     *
     * @param name
     */
    void getGuiName(QString &name);
    /**
     * @brief Get the Gui Comment object
     *
     * @param comment
     */
    void getGuiComment(QString &comment);
    /**
     * @brief Get the Gui Start State object
     *
     * @param startState
     */
    void getGuiStartState(QString &startState);
    /**
     * @brief
     *
     */
    void clearMachine();
    /**
     * @brief
     *
     * @param name
     */
    void deleteState(QString name);
    /**
     * @brief
     *
     * @param firstName
     * @param secondName
     */
    void deleteTransition(QString firstName, QString secondName);
};
