#ifndef CHANNELDIALOG_H
#define CHANNELDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class ChannelDialog : public QDialog
{
    Q_OBJECT

    QListWidget * m_channelsListWidget;
    QPushButton * m_selectButton;
    QLineEdit * m_nameEdit;
    QLineEdit *  m_latatitudeEdit;
    QLineEdit * m_longitudeEdit;
    QLabel * m_nameLabel;
    QLabel * m_longitudeLabel;
    QLabel * m_latatitudeLabel;

public:
    explicit ChannelDialog(/*QList<Channel> m_subscribedChannels,*/ QWidget *parent = 0);
    
signals:
    void onAccepted();
    
private slots:
    void onSelectButton();

public:
    QString getName();
    QString getLongitude();
    QString getLatatitude();
    QString getChannelName();
    
};

#endif // CHANNELDIALOG_H
