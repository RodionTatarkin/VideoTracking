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
    connect(cameraWidget, SIGNAL(downloadVideo()), this, SLOT(downloadVideo()));
    setCentralWidget(cameraWidget);
}

void MainWindow::downloadVideo()
{
    downloadVideoAction->setDisabled(TRUE);

    m_downloadVideoWidget = new downloadVideoWidget(this);

    setCentralWidget(m_downloadVideoWidget);

    QMessageBox messageBox(this);
    messageBox.setText("Now we're going to download Video to ftp server");
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.setIcon(QMessageBox::Information);
    messageBox.exec();

    m_downloadVideoWidget->onStartDownloadingVideo();

    // -- Login --
    /*LoginDialog loginDialog(this);
    loginDialog.exec();
    QString login;
    QString password;
    QString email;
    login = loginDialog.getLogin();
    password = loginDialog.getPassword();
    if (loginDialog.email)
        email = loginDialog.getEmail();
    qDebug() << login << password << email;*/

    /*if (loginDialog.email)
    {
        m_addUserQuery->setQuery(login, password, email);
        m_addUserQuery->doRequest();
    }
    else
    {
        m_loginQuery->setQuery(login, password);
        m_loginQuery->doRequest();
    }*/
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

    // загрузить видео
    downloadVideoAction = new QAction("&downloadVideo", this);
    downloadVideoAction->setStatusTip("Download Video to Geo2Tag");
    connect(downloadVideoAction, SIGNAL(triggered()), this, SLOT(downloadVideo()));
}

void MainWindow::createMenus()
{
    actionMenu = menuBar()->addMenu("&Actions");
    actionMenu->addAction(newVideoAction);
    actionMenu->addAction(downloadVideoAction);
    actionMenu->addSeparator();
    actionMenu->addAction(exitAction);
}
