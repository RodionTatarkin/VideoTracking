#include "mainwindow.h"
#include "cam.h"
#include "videowidget.h"
#include "player.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
    mainWindow.showExpanded();
    mainWindow.effectiveWinId();*/

    /*QCameraViewfinder * viewfinder = new QCameraViewfinder(NULL);
    viewfinder->show();*/

    /*Cam cam;
    cam.show();*/

    /*VideoWidget videowidget;
    videowidget.show();*/

    /*Player player;
    player.show();*/

    MainWindow mainWindow;
    mainWindow.show();

    //player.player->play();
    /*QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("D:/Japan.mkv"));
    QVideoWidget * videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);
    videoWidget->show();
    player->play();*/


    /*QDialog dialog(NULL);
    dialog.show();*/

    return app.exec();
}
