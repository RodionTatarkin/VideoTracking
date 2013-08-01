#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QSlider>
#include <QPushButton>
#include "videowidget.h"

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = 0);
    
signals:
    void play();
    
private slots:
    void displayErrorMessage();
    void positionChanged(qint64 progress);
    void durationChanged(qint64 duration);
    void seek(int seconds);
    void playClicked();

public:
    QMediaPlayer * player;
    QVideoWidget * videoWidget;
    QMediaPlaylist * playlist;
    QSlider * slider;
    QPushButton * playButton;
};

#endif // PLAYER_H
