#include "mainwindow.h"
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_videoTrackingWidget = new QLabel("Video Tracking", this);
    m_videoTrackingWidget->setAlignment(Qt::AlignCenter);
    setCentralWidget(m_videoTrackingWidget);
    m_downloadVideoWidget = NULL;
    m_cameraWidget = NULL;

    createActions();
    createMenus();
}

void MainWindow::newVideo()
{
    newVideoAction->setDisabled(true);

    m_cameraWidget = new Cam(this);
    connect(m_cameraWidget, SIGNAL(downloadVideo(GeoVideo)), this, SLOT(downloadVideo(GeoVideo)));
    setCentralWidget(m_cameraWidget);
}

void MainWindow::downloadVideo(GeoVideo currentVideo)
{
    m_downloadVideoWidget = new downloadVideoWidget(this);
    connect(this, SIGNAL(onStartDownloadingVideo(GeoVideo)), m_downloadVideoWidget, SLOT(onStartDownloadingVideo(GeoVideo)));
    connect(m_downloadVideoWidget, SIGNAL(finished()), this, SLOT(onFinished()));

    setCentralWidget(m_downloadVideoWidget);

    QMessageBox messageBox(this);
    messageBox.setText("Now we're going to download Video to ftp server");
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.setIcon(QMessageBox::Information);
    messageBox.exec();

    emit(onStartDownloadingVideo(currentVideo));
    //m_downloadVideoWidget->onStartDownloadingVideo(currentVideo);
}

void MainWindow::onFinished()
{
    m_videoTrackingWidget = new QLabel("Video Tracking", this);
    m_videoTrackingWidget->setAlignment(Qt::AlignCenter);
    setCentralWidget(m_videoTrackingWidget);
    m_downloadVideoWidget->close();
    newVideoAction->setDisabled(false);
    delete m_downloadVideoWidget;
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
