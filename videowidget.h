#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>

QT_USE_NAMESPACE

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    VideoWidget(QWidget *parent = 0);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // VIDEOWIDGET_H
