#include "mainwindow.h"
#include "cam.h"
#include "videowidget.h"
#include "player.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
