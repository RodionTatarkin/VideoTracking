#ifndef CREATECHANNELDIALOG_H
#define CREATECHANNELDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class CreateChannelDialog : public QDialog
{
    Q_OBJECT

    QListWidget * m_channelsListWidget;
    QPushButton * m_subscribeButton;
    QLabel * m_channelNameLabel;
    QLabel * m_descriptionLabel;
    QLabel * m_urlLabel;
    QLineEdit * m_channelNameEdit;
    QLineEdit * m_descriptionEdit;
    QLineEdit * m_urlEdit;
    QPushButton * m_addChannelButton;

public:
    explicit CreateChannelDialog(QWidget *parent = 0);

    QString getChannelName();
    QString getName();
    QString getDescription();
    QString getUrl();
    
signals:
    void onSubscribeAccepted();
    void onAddChannelAccepted();
    
private slots:
    void onSubscribeChannelButton();
    void onAddChannelButton();
    
};

#endif // CREATECHANNELDIALOG_H
