// File: mainwindow.h
// Author: Patrik Prochazka, Filip Ficka
// Login: xprochp00, xfickaf00

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FSMView.h"
#include "FSMScene.h"
#include "../parser/MooreMachine.h"
#include "../parser/IExecutionStrategy.h"
#include "FSMGui.h"
#include "GenericRowWidget.h"
#include "TransitionRowWidget.h"

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

    FSMScene *fsmScene;
    MooreMachine *machine;
    FSMView *fsmView;
    FSMGui *fsmGui;

    FSMState *selectedState = nullptr;

    QVBoxLayout *inputsLayout;
    QVBoxLayout *outputsLayout;
    QVBoxLayout *variablesLayout;

    QList<GenericRowWidget *> inputsWidgets;
    QList<GenericRowWidget *> outputsWidgets;
    QList<GenericRowWidget *> variablesWidgets;
    QList<TransitionRowWidget *> conditionWidgets;

signals:
    void loadJsonRequested(const QString &fileName, MooreMachine &machine);
    void exportJsonRequested(const QString &fileName, MooreMachine &machine);
    void createMachine(MooreMachine &machine);
    void clearMachine();
    void setStrategy(IExecutionStrategy *strategy);
    void executeMachine(MooreMachine &machine);

private slots:
    TransitionRowWidget *onAddTransitionClicked();
    void onCreateTransition(TransitionRowWidget *row);
    void onRemoveTransition(TransitionRowWidget *row);
    void onAddInputClicked();
    void onAddOutputClicked();
    void onAddVariableClicked();
    void onDeleteRow(GenericRowWidget *row);
    void onImportFileClicked();
    void onExportFileClicked();
    void onRunClicked();
    void showDetailsPanel(QGraphicsItem *item);

public:
    void clearTransitionRows();
    void detachWidgetsFromLayout(QLayout *layout);
};

#endif // MAINWINDOW_H
