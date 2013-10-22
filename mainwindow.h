#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include "cam.h"
#include "downloadvideowidget.h"
#include "geovideo.h"

class QMenu;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:
    void onStartDownloadingVideo(GeoVideo);

private slots:
    void newVideo();
    void downloadVideo(GeoVideo currentVideo);

    void onFinished();

private:
    void createActions();
    void createMenus();

    Cam * m_cameraWidget;
    downloadVideoWidget * m_downloadVideoWidget;
    QLabel * m_videoTrackingWidget;

    QAction * exitAction;
    QAction * newVideoAction;
    QAction * downloadVideoAction;

    QMenu * actionMenu;
    
};

#endif // MAINWINDOW_H
