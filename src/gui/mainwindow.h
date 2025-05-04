// File: mainwindow.h
// Author: Patrik Prochazka, Filip Ficka
// Login: xprochp00, xfickaf00

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FSMView.h"
#include "FSMScene.h"
#include "parser/MooreMachine.h"
#include "GenericRowWidget.h"
#include "ConditionRowWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    FSMView *fsmView;
    FSMScene *fsmScene;
    MooreMachine *machine;

    QVBoxLayout *inputsLayout;
    QVBoxLayout *outputsLayout;
    QVBoxLayout *variablesLayout;
    QList<ConditionRowWidget*> conditionWidgets;

signals:
    void loadJsonRequested(const QString &fileName, MooreMachine &machine);
    void exportJsonRequested(const QString &fileName, MooreMachine &machine);
    void createMachine(MooreMachine &machine);

private slots:
    void onAddRowButtonClicked();
    void onAddOutputClicked();
    void onAddVariableClicked();
    void onImportFileClicked();
    void onExportFileClicked();

    void onDeleteRow(GenericRowWidget *row);
    void clearConditionWidgets();
};

#endif // MAINWINDOW_H
