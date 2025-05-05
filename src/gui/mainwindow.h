// File: mainwindow.h
// Author: Patrik Prochazka, Filip Ficka
// Login: xprochp00, xfickaf00

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FSMView.h"
#include "FSMScene.h"
#include "FSMGui.h"
#include "GenericRowWidget.h"
#include "ConditionRowWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
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
    FSMView *fsmView;
    FSMGui *fsmGui;

    QVBoxLayout *inputsLayout;
    QVBoxLayout *outputsLayout;
    QVBoxLayout *variablesLayout;

    QList<GenericRowWidget*> inputsWidgets;
    QList<GenericRowWidget*> outputsWidgets;
    QList<GenericRowWidget*> variablesWidgets;
    QList<ConditionRowWidget*> conditionWidgets;

private slots:
    void onAddInputClicked();
    void onAddOutputClicked();
    void onAddVariableClicked();

    void onDeleteRow(GenericRowWidget *row);
    void showDetailsPanel(QGraphicsItem *item);

public:
    void clearConditionRows();
    void clearGenericRows();

    template <typename T>
    void clearWidgetsRows(QList<T*> &widgetRows) {
        for (T *row : widgetRows) {
            if (row) row->deleteLater();
        }
        widgetRows.clear();
    }

    GenericRowWidget* createGenericRow(QVBoxLayout *layout, QList<GenericRowWidget*> &rows, GenericRowWidget::RowType type);
    void displayGenericRow(QList<GenericRowWidget*> rows);
};

#endif // MAINWINDOW_H
