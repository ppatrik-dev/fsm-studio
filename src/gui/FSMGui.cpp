#include "FSMGui.h"

void FSMGui::saveInputs(const QList<GenericRowWidget*> &rows) {
    m_inputs.clear();

    for (auto row : rows) {
        QString key = row->key();
        QString value = row->value();

        if (key.isEmpty() || value.isEmpty()) {
            qDebug() << "Empty variable key or value";
            continue;
        }

        m_inputs.insert(key, value);
    }
}

void FSMGui::saveOutputs(const QList<GenericRowWidget*> &rows) {
    m_outputs.clear();

    for (auto row : rows) {
        QString key = row->key();
        QString value = row->value();

        if (key.isEmpty() || value.isEmpty()) {
            qDebug() << "Empty variable key or value";
            continue;
        }

        m_outputs.insert(key, value);
    }
}

void FSMGui::saveVariables(const QList<GenericRowWidget*> &rows) {
    m_variables.clear();

    for (auto row : rows) {
        QString key = row->key();
        QString value = row->value();

        if (key.isEmpty() || value.isEmpty()) {
            qDebug() << "Empty variable key or value";
            continue;
        }

        m_variables.insert(key, value);
    }
}
