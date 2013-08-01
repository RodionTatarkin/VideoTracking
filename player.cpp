#include "player.h"
#include <QMediaPlaylist>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QStyle>

Player::Player(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout * layout;
    player = new QMediaPlayer(this);

    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));

    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));

    videoWidget = new QVideoWidget(this);
    /*playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("D:\\Japan.mp4"));
    playlist->setCurrentIndex(0);
    player->setPlaylist(playlist);*/

    player->setVideoOutput(videoWidget);
    player->setMedia(QUrl::fromLocalFile("D://Japan.mp4"));

    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, player->duration() / 1000);
    //qDebug() << player->duration() << slider->maximum();
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));


    playButton = new QPushButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));
    connect(this, SIGNAL(play()), player, SLOT(play()));


    layout = new QVBoxLayout();
    layout->addWidget(videoWidget);
    layout->addWidget(slider);
    layout->addWidget(playButton);
    setLayout(layout);


    //player->play();

}

void Player::durationChanged(qint64 duration)
{
    slider->setMaximum(duration / 1000);
    qDebug() << player->duration() << duration;
}

void Player::positionChanged(qint64 progress)
{
    if (!slider->isSliderDown()) {
        slider->setValue(progress / 1000);
    }
    qDebug() << "100500\n";
}

void Player::displayErrorMessage()
{
    qDebug() << player->errorString();
    //setStatusInfo(player->errorString());
}

void Player::seek(int seconds)
{
    player->setPosition(seconds * 1000);
}

void Player::playClicked()
{
    emit play();
}
