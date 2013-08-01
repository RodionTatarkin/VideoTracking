#include "mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    /*QWidget * widget = new QWidget;
    setCentralWidget(widget);*/

    createActions();
    createMenus();
}

void MainWindow::newVideo()
{
    newVideoAction->setDisabled(TRUE);

    cameraWidget = new Cam(this);
    setCentralWidget(cameraWidget);
}
void MainWindow::createActions()
{
    // снять видео
    newVideoAction = new QAction("&newVideo", this);
    newVideoAction->setShortcuts(QKeySequence::New);
    newVideoAction->setStatusTip("Create new Video");
    connect(newVideoAction, SIGNAL(triggered()), this, SLOT(newVideo()));

    // выйти из приложения
    exitAction = new QAction("E&xit", this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip("Exit the application");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
    actionMenu = menuBar()->addMenu("&Actions");
    actionMenu->addAction(newVideoAction);
    //actionMenu->addSeparator();
    actionMenu->addAction(exitAction);
}
