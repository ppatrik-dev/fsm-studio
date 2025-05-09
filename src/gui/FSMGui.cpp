#include "FSMGui.h"

void FSMGui::setInitialState(FSMState *state)
{
    if (m_initialState == state)
        return;

    if (m_initialState)
        m_initialState->setInitial(false);

    m_initialState = state;

    if (m_initialState)
        m_initialState->setInitial(true);

    if (state) {
        emit initialStateChanged(state->getLabel());
    }
    else {
        emit initialStateChanged("");
    }
}

void FSMGui::saveInputs(const QList<GenericRowWidget *> rows)
{
    QList<QString> used_id;

    for (GenericRowWidget *row : rows)
    {
        QString key = row->key();
        QString value = row->value();

        if (used_id.contains(key))
        {
            qDebug() << "Input with name " << key << " already defined";
            emit row->requestDelete(row);
            continue;
        }

        if (key.isEmpty())
        {
            emit row->requestDelete(row);
            continue;
        }

        if (m_inputs.contains(key))
        {
            if (m_inputs.value(key) != value)
            {
                m_inputs[key] = value;
                emit inputAddValue(key, value);
            }
        }
        else
        {
            m_inputs.insert(key, value);
            emit inputAddValue(key, value);
        }

        used_id.append(key);
        row->disableKeyEdit();
    }
}

void FSMGui::deleteInput(const QString &key)
{
    m_inputs.remove(key);
    emit inputDeleteValue(key);
}

void FSMGui::saveOutputs(const QList<GenericRowWidget *> rows)
{
    QList<QString> used_id;

    for (GenericRowWidget *row : rows)
    {
        QString key = row->key();
        QString value = row->value();

        if (used_id.contains(key))
        {
            qDebug() << "Output with name " << key << " already defined";
            emit row->requestDelete(row);
            continue;
        }

        if (key.isEmpty())
        {
            emit row->requestDelete(row);
            continue;
        }

        if (m_outputs.contains(key))
        {
            if (m_outputs.value(key) != value)
            {
                m_outputs[key] = value;
                emit outputAddValue(key, value);
            }
        }
        else
        {
            m_outputs.insert(key, value);
            emit outputAddValue(key, value);
        }

        used_id.append(key);
        row->disableKeyEdit();
    }
}

void FSMGui::deleteOutput(const QString &key)
{
    m_outputs.remove(key);
    emit outputDeleteValue(key);
}

void FSMGui::saveVariables(const QList<GenericRowWidget *> rows)
{
    QList<QString> used_id;

    for (GenericRowWidget *row : rows)
    {
        QString key = row->key();
        QString value = row->value();

        if (used_id.contains(key))
        {
            qDebug() << "Variable with name " << key << " already defined";
            emit row->requestDelete(row);
            continue;
        }

        if (key.isEmpty())
        {
            emit row->requestDelete(row);
            continue;
        }

        if (m_outputs.contains(key))
        {
            if (m_variables.value(key) != value)
            {
                m_variables[key] = value;
                qDebug() << key << value;
                emit variableAddValue(key, value);
            }
        }
        else
        {
            m_variables.insert(key, value);
            emit variableAddValue(key, value);
        }

        used_id.append(key);
        row->disableKeyEdit();
    }
}

void FSMGui::deleteVariable(const QString &key)
{
    m_inputs.remove(key);
    emit variableDeleteValue(key);
}

void FSMGui::importDetails() {
    emit getNameValue(m_name);
    emit getDescriptionValue(m_description);
    emit getVarValue(m_inputs, "input");
    emit getVarValue(m_outputs, "output");
    emit getVarValue(m_variables, "variable");

    QString stateLabel;
    emit getStartStateValue(stateLabel);
    setInitialState(m_graph->getStateByName(stateLabel));

    emit displayDetailsRequested();
}
