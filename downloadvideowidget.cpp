#include "downloadvideowidget.h"
#include <QVBoxLayout>
#include "logindialog.h"
#include "channeldialog.h"
#include "ftpdialog.h"
#include <QDebug>
#include <QMessageBox>
#include "errno.h"
#include "SettingsStorage.h"

downloadVideoWidget::downloadVideoWidget(QWidget *parent) :
    QWidget(parent)
{
    SettingsStorage::init();

    m_downloadVideoLabel = new QLabel(this);
    m_downloadVideoLabel->setText("Downloading Video");
    m_downloadVideoLabel->setAlignment(Qt::AlignCenter);

    setLayout(new QVBoxLayout());
    layout()->addWidget(m_downloadVideoLabel);

    initQueries();

}

void downloadVideoWidget::initQueries()
{
    m_loginQuery = new LoginQuery(this);
    m_addUserQuery = new AddUserQuery(this);
    m_availableChannelsQuery = new AvailableChannelsQuery();
    m_subscribedChannelsQuery = new SubscribedChannelsQuery();
    m_subscribeChannelQuery = new SubscribeChannelQuery();
    m_writeTagQuery = new WriteTagQuery();
    m_applyChannelQuery = new ApplyChannelQuery();


    connect(m_loginQuery,SIGNAL(success()),this, SLOT(onLoginSuccess()));
    connect(m_loginQuery, SIGNAL(errorOccured(int)), this, SLOT(onLoginRequestError(int)));

    connect(m_addUserQuery, SIGNAL(success()), this, SLOT(onLoginSuccess()));
    connect(m_addUserQuery, SIGNAL(errorOccured(int)), this, SLOT(onLoginRequestError(int)));

    connect(m_availableChannelsQuery,SIGNAL(success()),this, SLOT(onAvailableChannelsSuccess()));
    connect(m_availableChannelsQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));

    connect(m_subscribedChannelsQuery,SIGNAL(success()),this, SLOT(onSubscribedChannelsSuccess()));
    connect(m_subscribedChannelsQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));

    connect(m_subscribeChannelQuery,SIGNAL(success()),this, SLOT(onChannelSubscribeSuccess()));
    connect(m_subscribeChannelQuery,SIGNAL(errorOccured(int)),this, SLOT(onChannelSubscribeRequestError(int)));

    connect(m_applyChannelQuery,SIGNAL(success()),this, SLOT(onApplyChannelSuccess()));
    connect(m_applyChannelQuery,SIGNAL(errorOccured(int)),this, SLOT(onApplyChannelRequestError(int)));

    connect(m_writeTagQuery, SIGNAL(success()), this, SLOT(onWriteTagSuccess()));
    connect(m_writeTagQuery, SIGNAL(errorOccured(int)), this, SLOT(onChannelRequestError(int)));
}

void downloadVideoWidget::onLoginSuccess()
{
    qDebug() << "Recieved session token! " << m_loginQuery->getSession();

#ifndef QT_NO_CURSOR
        setCursor(Qt::ArrowCursor);
#endif
    loginDialog->accept();
    QMessageBox::information(this, "Login Success", "You've successfully logined");

    m_session = m_loginQuery->getSession();

    m_availableChannelsQuery->setQuery(m_session);
    m_availableChannelsQuery->doRequest();
}

void downloadVideoWidget::getSubscribedChannels()
{
    m_subscribedChannelsQuery->setQuery(m_session);
    m_subscribedChannelsQuery->doRequest();
}

void downloadVideoWidget::onAvailableChannelsSuccess()
{
    qDebug() <<"MainWindow::onAvailableChannelsSuccess()";

    getSubscribedChannels();
}

void downloadVideoWidget::formChannelList()
{
    if (m_subscribedChannelsQuery->getChannels().size() == 0)
    {
        QMessageBox::information(this, "Channels", "you don't have subscribed Channels. You have to create one or subscribe");
        m_availableChannels = m_availableChannelsQuery->getChannels();
        createChannelDialog = new CreateChannelDialog(m_availableChannels, this);
        connect(createChannelDialog, SIGNAL(onSubscribeAccepted()), this, SLOT(onSubscribeAccepted()));
        connect(createChannelDialog, SIGNAL(onAddChannelAccepted()), this, SLOT(onAddChannelAccepted()));
        createChannelDialog->exec();
        m_subscribedChannelsQuery->setQuery(m_session);
        m_subscribedChannelsQuery->doRequest();
    }
    else
    {
        m_subscribedChannels = m_subscribedChannelsQuery->getChannels();
        channelDialog = new ChannelDialog(m_subscribedChannels, currentVideo.url, this);
        connect(channelDialog, SIGNAL(onAccepted()), this, SLOT(onChannelAccepted()));
        channelDialog->exec();
    }
}

void downloadVideoWidget::onSubscribedChannelsSuccess()
{
    qDebug()<<"MainWindow::onSubscribedChannelsSuccess()";

    formChannelList();
}

void downloadVideoWidget::onWriteTagSuccess()
{
    doneRequests++;
    if (doneRequests == currentVideo.geoTags.count())
    {
#ifndef QT_NO_CURSOR
        setCursor(Qt::ArrowCursor);
#endif
        channelDialog->accept();
        QMessageBox::information(this, "Write Tag Success", "You've successfully written Tags");
    }
    else
    {
        m_writeTagQuery->setTag(Tag(0.0, currentVideo.geoTags.at(doneRequests).coordinate().latitude(), currentVideo.geoTags.at(doneRequests).coordinate().longitude(), m_name, currentVideo.time.at(doneRequests), currentVideo.url));
        m_writeTagQuery->doRequest();
    }
    //writeToStatusLog("WriteTag request succeed");
}

void downloadVideoWidget::onChannelSubscribeSuccess()
{
#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
#endif
    createChannelDialog->accept();
    QMessageBox::information(this, "Subscribe to Channel", "You've successfully subscribed to Channel");
}

void downloadVideoWidget::onApplyChannelSuccess()
{
#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
#endif
    createChannelDialog->accept();
    QMessageBox::information(this, "New Channel", "You've successfully created new Channel");
}

void downloadVideoWidget::onLoginRequestError(int err)
{
#ifndef QT_NO_CURSOR
        setCursor(Qt::ArrowCursor);
        loginDialog->setCursor(Qt::ArrowCursor);
#endif
    /*writeToStatusLog("Error processing "+
                         QString(this->sender()->metaObject()->className())+", errno = " +
                         QString::number(errno)+", type = " + Errno::initErrnoMap().value(errno));*/
    qDebug() << "Error "<< err << " occured";

    /*QMessageBox::warning(this, "Error Occured", "Error processing "+
                         QString(this->sender()->metaObject()->className())+", errno = " +
                         QString::number(err)+", type = " + Errno::initErrnoMap().value(err));*/
    QMessageBox::warning(this, "Error Uccured", "Error:" + QString::number(err) + "Try Again");

    loginDialog->setEnabled(true);
}

void downloadVideoWidget::onChannelRequestError(int err)
{
#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
    loginDialog->setCursor(Qt::ArrowCursor);
#endif
    /*writeToStatusLog("Error processing "+
                         QString(this->sender()->metaObject()->className())+", errno = " +
                         QString::number(errno)+", type = " + Errno::initErrnoMap().value(errno));*/
    qDebug() << "Error "<< err << " occured";

    /*QMessageBox::warning(this, "Error Occured", "Error processing "+
                         QString(this->sender()->metaObject()->className())+", errno = " +
                         QString::number(err)+", type = " + Errno::initErrnoMap().value(err));*/
    QMessageBox::warning(this, "Error Uccured", "Error:" + QString::number(err) + "Try Again");
    channelDialog->setEnabled(true);
}

void downloadVideoWidget::onChannelSubscribeRequestError(int err)
{
#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
    createChannelDialog->setCursor(Qt::ArrowCursor);
#endif
    /*writeToStatusLog("Error processing "+
                         QString(this->sender()->metaObject()->className())+", errno = " +
                         QString::number(errno)+", type = " + Errno::initErrnoMap().value(errno));*/
    qDebug() << "Error "<< err << " occured";

    /*QMessageBox::warning(this, "Error Occured", "Error processing "+
                         QString(this->sender()->metaObject()->className())+", errno = " +
                         QString::number(err)+", type = " + Errno::initErrnoMap().value(err));*/
    QMessageBox::warning(this, "Error Uccured", "Error:" + QString::number(err) + "Try Again");
    createChannelDialog->setEnabled(true);
}

void downloadVideoWidget::onApplyChannelRequestError(int err)
{
#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
    createChannelDialog->setCursor(Qt::ArrowCursor);
#endif
    /*writeToStatusLog("Error processing "+
                         QString(this->sender()->metaObject()->className())+", errno = " +
                         QString::number(errno)+", type = " + Errno::initErrnoMap().value(errno));*/
    qDebug() << "Error "<< err << " occured";

    /*QMessageBox::warning(this, "Error Occured", "Error processing "+
                         QString(this->sender()->metaObject()->className())+", errno = " +
                         QString::number(err)+", type = " + Errno::initErrnoMap().value(err));*/
    QMessageBox::warning(this, "Error Uccured", "Error:" + QString::number(err) + "Try Again");
    createChannelDialog->setEnabled(true);
}

void downloadVideoWidget::onLoginAccepted()
{
#ifndef QT_NO_CURSOR
        setCursor(Qt::WaitCursor);
#endif

    SettingsStorage::setValue("server_url",QVariant("http://demo64.geo2tag.org/"),"common");
    SettingsStorage::setValue("server_port",QVariant("80"),"common");
    qDebug() << SettingsStorage::getValue("common/server_url", QVariant(DEFAULT_SERVER)).toString() <<  SettingsStorage::getValue("common/server_port", QVariant(DEFAULT_PORT)).toString();

    QString login;
    QString password;
    QString email;
    login = loginDialog->getLogin();
    password = loginDialog->getPassword();
    if (loginDialog->email)
        email = loginDialog->getEmail();
    qDebug() << login << password << email;

    if (loginDialog->email)
    {
        m_addUserQuery->setQuery(login, password, email);
        m_addUserQuery->doRequest();
    }
    else
    {
        m_loginQuery->setQuery(login, password);
        m_loginQuery->doRequest();
    }
}

void downloadVideoWidget::onChannelAccepted()
{
#ifndef QT_NO_CURSOR
        setCursor(Qt::WaitCursor);
#endif
    QString channelName = channelDialog->getChannelName();
    //QString channelName = "Rodion";

    Channel channel(channelName);

    m_name = channelDialog->getName();

    doneRequests = 0;
    m_writeTagQuery->setChannel(channel);
    m_writeTagQuery->setSession(m_session);
    m_writeTagQuery->setTag(Tag(0.0, currentVideo.geoTags.at(0).coordinate().latitude(), currentVideo.geoTags.at(0).coordinate().longitude(), m_name, currentVideo.time.at(0), currentVideo.url));
    m_writeTagQuery->doRequest();
}

void downloadVideoWidget::onSubscribeAccepted()
{
#ifndef QT_NO_CURSOR
    setCursor(Qt::WaitCursor);
#endif

    QString channelName = createChannelDialog->getChannelName();
    Channel channel(channelName);
    //do subscribe
    m_subscribeChannelQuery->setQuery(channel, m_session);
    m_subscribeChannelQuery->doRequest();
}

void downloadVideoWidget::onAddChannelAccepted()
{
#ifndef QT_NO_CURSOR
    setCursor(Qt::WaitCursor);
#endif

    QString name = createChannelDialog->getName();
    QString description = createChannelDialog->getDescription();
    QString url = createChannelDialog->getUrl();

    m_applyChannelQuery->setQuery(Channel(name, description, url), m_session);
    m_applyChannelQuery->doRequest();
}

void downloadVideoWidget::onRequestError(int err)
{
    /*writeToStatusLog("Error processing "+
                     QString(this->sender()->metaObject()->className())+", errno = " +
                     QString::number(errno)+", type = " + Errno::initErrnoMap().value(errno));*/
    qDebug() << "Error "<< errno << " occured";
}

void downloadVideoWidget::onStartDownloadingVideo(GeoVideo video)
{
    currentVideo = video;
    // -- ftp server --
    FtpDialog ftpDialog(this, currentVideo.pathToVideo, currentVideo.videoName);
    connect(&ftpDialog, SIGNAL(rejected()), this, SLOT(close()));
    if (ftpDialog.exec())
    {
        currentVideo.url = ftpDialog.getUrlToVideoFile();
        qDebug() << currentVideo.url;

        // -- Login --
        loginDialog = new LoginDialog(this);
        connect(loginDialog, SIGNAL(onAccepted()), this, SLOT(onLoginAccepted()));
        loginDialog->exec();
    }
}
