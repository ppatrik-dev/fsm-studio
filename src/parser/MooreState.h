/**
 * @file MooreState.h
 * @author Miroslav Basista (xbasism00@vutbr.cz)
 * @brief
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "IMooreState.h"
#include "MooreTransition.h"
#include <QVector>
#include <QString>
/**
 * @brief
 *
 */
class MooreState : public IMooreState
{
    QString name;
    QString output;

public:
    QVector<MooreTransition> transitions;
    /**
     * @brief Construct a new Moore State object
     *
     * @param name
     * @param output
     */
    MooreState(const QString &name, const QString &output);
    /**
     * @brief Get the Name object
     *
     * @return QString
     */
    QString getName() const override;
    /**
     * @brief Get the Output object
     *
     * @return QString
     */
    QString getOutput() const override;
    /**
     * @brief Set the Output object
     *
     * @param value
     */
    void setOutput(QString value);
    /**
     * @brief Get the Transitions object
     *
     * @return QVector<MooreTransition>&
     */
    QVector<MooreTransition> &getTransitions();
    /**
     * @brief
     *
     * @param conditionText
     * @param toStateText
     */
    void addConditionByTransition(QString conditionText, QString toStateText);
    /**
     * @brief
     *
     * @param target
     * @return MooreTransition*
     */
    MooreTransition *findTransitionByTarget(QString &target);
    /**
     * @brief
     *
     * @param input
     * @param target
     */
    void addTransition(const QString &input, const QString &target) override;
    /**
     * @brief
     *
     * @param target
     */
    void deleteTransitionByTarget(const QString &target);
};
