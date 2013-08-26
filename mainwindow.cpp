#include "mainwindow.h"
#include <QPushButton>
#include <QMessageBox>

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
    connect(cameraWidget, SIGNAL(downloadVideo(GeoVideo)), this, SLOT(downloadVideo(GeoVideo)));
    setCentralWidget(cameraWidget);
}

void MainWindow::downloadVideo(GeoVideo currentVideo)
{
    m_downloadVideoWidget = new downloadVideoWidget(this);

    setCentralWidget(m_downloadVideoWidget);

    QMessageBox messageBox(this);
    messageBox.setText("Now we're going to download Video to ftp server");
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.setIcon(QMessageBox::Information);
    messageBox.exec();

    m_downloadVideoWidget->onStartDownloadingVideo(currentVideo);
}



void MainWindow::createActions()
{
    newVideoAction = new QAction("&newVideo", this);
    newVideoAction->setShortcuts(QKeySequence::New);
    newVideoAction->setStatusTip("Create new Video");
    connect(newVideoAction, SIGNAL(triggered()), this, SLOT(newVideo()));

    exitAction = new QAction("E&xit", this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip("Exit the application");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    /*downloadVideoAction = new QAction("&downloadVideo", this);
    downloadVideoAction->setStatusTip("Download Video to Geo2Tag");
    connect(downloadVideoAction, SIGNAL(triggered()), this, SLOT(downloadVideo()));*/
}

void MainWindow::createMenus()
{
    actionMenu = menuBar()->addMenu("&Actions");
    actionMenu->addAction(newVideoAction);
    //actionMenu->addAction(downloadVideoAction);
    actionMenu->addSeparator();
    actionMenu->addAction(exitAction);
}
