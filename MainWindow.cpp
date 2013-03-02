#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "Application.hpp"
#include <QActionGroup>
#include <QKeyEvent>
#include <QUndoStack>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *undoAction = qApp->undoStack()->createUndoAction(this);
    undoAction->setShortcut(QKeySequence("Ctrl+Z"));
    ui->menuEdit->addAction(undoAction);

    QAction *redoAction = qApp->undoStack()->createRedoAction(this);
    redoAction->setShortcut(QKeySequence("Ctrl+Y"));
    ui->menuEdit->addAction(redoAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}
