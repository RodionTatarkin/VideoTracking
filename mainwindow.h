#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include "cam.h"
#include "downloadvideowidget.h"

class QMenu;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

private slots:
    void newVideo();
    void downloadVideo(QString pathToVideoFile);

private:
    void createActions();
    void createMenus();

    Cam * cameraWidget;
    downloadVideoWidget * m_downloadVideoWidget;

    QAction * exitAction;
    QAction * newVideoAction;
    QAction * downloadVideoAction;

    QMenu * actionMenu;
    
};

#endif // MAINWINDOW_H
