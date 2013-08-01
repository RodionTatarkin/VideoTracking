#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include "cam.h"

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

private:
    void createActions();
    void createMenus();

    Cam * cameraWidget;

    QAction * exitAction;
    QAction * newVideoAction;
    QAction * requestAction;
    QAction * openVideoAction;

    QMenu * actionMenu;
    
};

#endif // MAINWINDOW_H
