#include "FSMGui.h"

void FSMGui::runSimulation(Ui::MainWindow *ui) {
    simulationMode = true;
    ui->runButton->setStyleSheet("background-color: rgb(51, 153, 102);");
}

void FSMGui::saveInputs(const QList<GenericRowWidget*> rows) {
    QList<QString> used_id;

    for (GenericRowWidget *row : rows) {
        QString key = row->key();
        QString value = row->value();

        if (used_id.contains(key)) {
            qDebug() << "Input with name " << key << " already defined";
            emit row->requestDelete(row);
            continue;
        }

        if (key.isEmpty()) {
            emit row->requestDelete(row);
            continue;
        }

        if (m_inputs.contains(key)) {
            if (m_inputs.value(key) != value) {
                m_inputs[key] = value;
                // TODO: Emit input value change signal to Mirek
            }
        }
        else {
            m_inputs.insert(key, value);
            // TODO: Emit input add signal to Mirek
        }

        used_id.append(key);
        row->disableKeyEdit();
    }
}

void FSMGui::deleteInput(const QString &key) {
    m_inputs.remove(key);
    // TODO: Emit input delete signal to Mirek
}

void FSMGui::saveOutputs(const QList<GenericRowWidget*> rows) {
    QList<QString> used_id;

    for (GenericRowWidget *row : rows) {
        QString key = row->key();
        QString value = row->value();

        if (used_id.contains(key)) {
            qDebug() << "Output with name " << key << " already defined";
            emit row->requestDelete(row);
            continue;
        }

        if (key.isEmpty()) {
            emit row->requestDelete(row);
            continue;
        }

        if (m_outputs.contains(key)) {
            if (m_outputs.value(key) != value) {
                m_outputs[key] = value;
                // TODO: Emit output value change signal to Mirek
            }
        }
        else {
            m_outputs.insert(key, value);
            // TODO: Emit output add signal to Mirek
        }

        used_id.append(key);
        row->disableKeyEdit();
    }
}

void FSMGui::deleteOutput(const QString &key) {
    m_outputs.remove(key);
    // TODO: Emit output delete signal to Mirek
}

void FSMGui::saveVariables(const QList<GenericRowWidget*> rows) {
    QList<QString> used_id;

    for (GenericRowWidget *row : rows) {
        QString key = row->key();
        QString value = row->value();

        if (used_id.contains(key)) {
            qDebug() << "Variable with name " << key << " already defined";
            emit row->requestDelete(row);
            continue;
        }

        if (key.isEmpty()) {
            emit row->requestDelete(row);
            continue;
        }

        if (m_outputs.contains(key)) {
            if (m_variables.value(key) != value) {
                m_variables[key] = value;
                // TODO: Emit variable value change signal to Mirek
            }
        }
        else {
            m_variables.insert(key, value);
            // TODO: Emit variable add signal to Mirek
        }

        used_id.append(key);
        row->disableKeyEdit();
    }
}

void FSMGui::deleteVariable(const QString &key) {
    m_inputs.remove(key);
    // TODO: Emit variable delete signal to Mirek
}
