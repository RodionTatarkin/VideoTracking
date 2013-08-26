#ifndef CHANNELDIALOG_H
#define CHANNELDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "Channel.h"

class ChannelDialog : public QDialog
{
    Q_OBJECT

    QListWidget * m_channelsListWidget;
    QPushButton * m_selectButton;
    QLineEdit * m_nameEdit;
    QLabel * m_nameLabel;
    QLabel * m_linkLabel;

public:
    explicit ChannelDialog(QList<Channel> m_subscribedChannels, QString url, QWidget *parent);
    
signals:
    void onAccepted();
    
private slots:
    void onSelectButton();

public:
    QString getName();
    QString getChannelName();
    
};

#endif // CHANNELDIALOG_H
