// File: mainwindow.cpp
// Author: Patrik Prochazka
// Login: xprochp00

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FSMView.h"
#include "FSMScene.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fsmView = ui->fsmGraphicsView;
    fsmScene = new FSMScene(this);
    fsmView->setScene(fsmScene);

    connect(ui->zoomInButton, &QPushButton::clicked, ui->fsmGraphicsView, &FSMView::zoomIn);
    connect(ui->zoomOutButton, &QPushButton::clicked, ui->fsmGraphicsView, &FSMView::zoomOut);
    connect(ui->fsmGraphicsView, &FSMView::zoomChanged, this, [=](int percent) {
        ui->zoomLabel->setText(QString::number(percent) + "%");
    });

    connect(fsmView, &FSMView::addStateRequested, fsmScene, &FSMScene::onAddState);
    connect(fsmView, &FSMView::addTransitionRequested, fsmScene, &FSMScene::onAddTransition);
    connect(fsmView, &FSMView::deleteStateRequested, fsmScene, &FSMScene::onDeleteState);
    connect(fsmView, &FSMView::deleteTransitionRequested, fsmScene, &FSMScene::onDeleteTransition);

    connect(fsmScene, &FSMScene::itemSelected, this, [=](QGraphicsItem *item) {
        if (!item) {
            ui->rightPanel->setCurrentWidget(ui->automataPropertiesPanel);
        }
        else if (item->type() == FSMState::Type) {
            ui->rightPanel->setCurrentWidget(ui->statePropertiesPanel);
        }
        else if (item->type() == FSMTransition::Type) {
            ui->rightPanel->setCurrentWidget(ui->transitionPropertiesPanel);
        }
        else {
            ui->rightPanel->setCurrentWidget(ui->automataPropertiesPanel);
        }
    });
}
MainWindow::~MainWindow()
{
    delete ui;
}
