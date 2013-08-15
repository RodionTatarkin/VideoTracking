#ifndef DOWNLOADVIDEOWIDGET_H
#define DOWNLOADVIDEOWIDGET_H

#include <QWidget>
#include <QLabel>

class downloadVideoWidget : public QWidget
{
    Q_OBJECT

    QLabel * m_downloadVideoLabel;

    //Session m_session;

    /*LoginQuery * m_loginQuery;
    AddUserQuery * m_addUserQuery;
    AvailableChannelsQuery * m_availableChannelsQuery;
    SubscribedChannelsQuery * m_subscribedChannelsQuery;
    SubscribeChannelQuery * m_subscribeChannelQuery;
    UnsubscribeChannelQuery * m_unsubscribeChannelQuery;
    LoadTagsQuery * m_loadTagsQuery;
    WriteTagQuery * m_writeTagQuery;
    ApplyChannelQuery * m_applyChannelQuery;*/

    void initQueries();

    void getSubscribedChannels();

    void formChannelList();

private slots:
    void onLoginSuccess();
    void onAvailableChannelsSuccess();
    void onSubscribedChannelsSuccess();

public:
    explicit downloadVideoWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void onStartDownloadingVideo(QString pathToVideoFile);
    
};

#endif // DOWNLOADVIDEOWIDGET_H
