#include "videowidget.h"
#include <QtGui>

VideoWidget::VideoWidget(QWidget *parent)
        : QVideoWidget(parent)
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::white);
    setPalette(p);

    setAttribute(Qt::WA_OpaquePaintEvent);
}


void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    setFullScreen(!isFullScreen());

    event->accept();
}

