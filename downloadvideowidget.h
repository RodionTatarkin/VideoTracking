#ifndef DOWNLOADVIDEOWIDGET_H
#define DOWNLOADVIDEOWIDGET_H

#include <QWidget>
#include <QLabel>
#include "logindialog.h"
#include "channeldialog.h"
#include "createchanneldialog.h"
#include "LoginQuery.h"
#include "AddUserQuery.h"
#include "AvailableChannelsQuery.h"
#include "SubscribedChannelsQuery.h"
#include "SubscribeChannelQuery.h"
#include "WriteTagQuery.h"
#include "ApplyChannelQuery.h"
#include "Channel.h"
#include "geovideo.h"
#include <QProgressDialog>
#include "ftpdialog.h"
#include "setdbquery.h"

class downloadVideoWidget : public QWidget
{
    Q_OBJECT

    int doneRequests;
    QString m_name;

    QLabel * m_downloadVideoLabel;

    QProgressDialog * m_progressDialog;

    LoginDialog * loginDialog;
    ChannelDialog * channelDialog;
    CreateChannelDialog * createChannelDialog;
    FtpDialog * ftpDialog;

    Session m_session;

    QList<Channel> m_subscribedChannels;
    QList<Channel> m_availableChannels;

    LoginQuery * m_loginQuery;
    AddUserQuery * m_addUserQuery;
    AvailableChannelsQuery * m_availableChannelsQuery;
    SubscribedChannelsQuery * m_subscribedChannelsQuery;
    SubscribeChannelQuery * m_subscribeChannelQuery;
    WriteTagQuery * m_writeTagQuery;
    ApplyChannelQuery * m_applyChannelQuery;
    SetDBQuery * m_setDBQuery;

    GeoVideo currentVideo;

    void initQueries();

    void getSubscribedChannels();

    //void formChannelList();

private slots:
    void formChannelList();

    void onLoginSuccess();
    void onAvailableChannelsSuccess();
    void onSubscribedChannelsSuccess();
    void onWriteTagSuccess();
    void onChannelSubscribeSuccess();
    void onApplyChannelSuccess();
    void onSetDBSuccess();

    void onRequestError(int err);
    void onLoginRequestError(int err);
    void onChannelRequestError(int err);
    void onChannelSubscribeRequestError(int err);
    void onApplyChannelRequestError(int err);
    void onSetDBRequestError(int err);

    void onLoginAccepted();
    void onChannelAccepted();
    void onSubscribeAccepted();
    void onAddChannelAccepted();

    void onStartDownloadingVideo(GeoVideo video);

public:
    explicit downloadVideoWidget(QWidget *parent = 0);
    
signals:
    void finished();
    
/*public slots:
    void onStartDownloadingVideo(GeoVideo video);*/
    
};

#endif // DOWNLOADVIDEOWIDGET_H
