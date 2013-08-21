#include "downloadvideowidget.h"
#include <QVBoxLayout>
#include "logindialog.h"
#include "channeldialog.h"
#include "ftpdialog.h"
#include <QDebug>
#include <QMessageBox>
#include "errno.h"

downloadVideoWidget::downloadVideoWidget(QWidget *parent) :
    QWidget(parent)
{
    m_downloadVideoLabel = new QLabel(this);
    m_downloadVideoLabel->setText("Downloading Video");
    m_downloadVideoLabel->setAlignment(Qt::AlignCenter);

    setLayout(new QVBoxLayout());
    layout()->addWidget(m_downloadVideoLabel);

    initQueries();

}

void downloadVideoWidget::initQueries()
{
    /*m_loginQuery = new LoginQuery(this);
    m_addUserQuery = new AddUserQuery(this);
    m_availableChannelsQuery = new AvailableChannelsQuery(this);
    m_subscribedChannelsQuery = new SubscribedChannelsQuery(this);
    m_subscribeChannelQuery = new SubscribeChannelQuery(this);
    m_writeTagQuery = new WriteTagQuery(this);
    m_applyChannelQuery = new ApplyChannelQuery(this);


    connect(m_loginQuery,SIGNAL(success()),this, SLOT(onLoginSuccess()));
    connect(m_loginQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));
    connect(m_loginQuery, SIGNAL(qrrorOccured(int)), this, SLOT(onLoginRequestError(int)));

    connect(m_loginQuery, SIGNAL(success()), this, SLOT(onLoginSuccess()));
    connect(m_addUserQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));
    connect(m_loginQuery, SIGNAL(errorOccured(int)), this, SLOT(onLoginRequestError(int)));

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
    connect(m_writeTagQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));*/
}

void downloadVideoWidget::onLoginSuccess()
{
    /*qDebug() << "Recieved session token! " << m_loginQuery->getSession();

#ifndef QT_NO_CURSOR
        setCursor(Qt::ArrowCursor);
#endif
    loginDialog->accept();
    QMessageBox::information(this, "Login Success", "You've' successfully logined");

    m_session = m_loginQuery->getSession();

    m_availableChannelsQuery->setQuery(m_session);
    m_availableChannelsQuery->doRequest();

    */
}

void downloadVideoWidget::getSubscribedChannels()
{
    /*m_subscribedChannelsQuery->setQuery(m_session);
    m_subscribedChannelsQuery->doRequest();*/
}

void downloadVideoWidget::onAvailableChannelsSuccess()
{
    /*qDebug() <<"MainWindow::onAvailableChannelsSuccess()";

    getSubscribedChannels();*/
}

void downloadVideoWidget::formChannelList()
{
    /*if (m_subscribedChannelsQuery->getChannels().size() == 0)
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
        channelDialog = new ChannelDialog(m_subscribedChannels, this);
        connect(channelDialog, SIGNAL(onAccepted()), this, SLOT(onChannelAccepted()));
        channelDialog->exec();
    }*/
}

void downloadVideoWidget::onSubscribedChannelsSuccess()
{
    /*qDebug()<<"MainWindow::onSubscribedChannelsSuccess()";

    formChannelList();*/
}

void downloadVideoWidget::onWriteTagSuccess()
{
    //writeToStatusLog("WriteTag request succeed");

#ifndef QT_NO_CURSOR
        setCursor(Qt::ArrowCursor);
#endif
    channelDialog->accept();
    QMessageBox::information(this, "Write Tag Success", "You've successfully written Tag  ");
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
    createChannelDialog->setEnabled(true);
}

void downloadVideoWidget::onLoginAccepted()
{
#ifndef QT_NO_CURSOR
        setCursor(Qt::WaitCursor);
#endif
    QString login;
    QString password;
    QString email;
    login = loginDialog->getLogin();
    password = loginDialog->getPassword();
    if (loginDialog->email)
        email = loginDialog->getEmail();
    qDebug() << login << password << email;

    /*if (loginDialog.email)
    {
        m_addUserQuery->setQuery(login, password, email);
        m_addUserQuery->doRequest();
    }
    else
    {
        m_loginQuery->setQuery(login, password);
        m_loginQuery->doRequest();
    }*/
}

void downloadVideoWidget::onChannelAccepted()
{
/*#ifndef QT_NO_CURSOR
        setCursor(Qt::WaitCursor);
#endif
    int index = channelDialog.getCurrentRow();
    qDebug() << "current row:" << index;
    QString channelName = channelDialog->getChannelName();

    Channel channel(channelName);

    qreal lat = channelDialog.getLatatitude().toDouble();
    qreal lon = channelDialog.getLongitude().toDouble();
    QString name = channelDialog.getName();

    m_writeTagQuery->setChannel(channel);
    m_writeTagQuery->setSession(m_session);
    m_writeTagQuery->setTag(Tag(0.0, lat, lon, name));
    m_writeTagQuery->doRequest();*/
}

void downloadVideoWidget::onSubscribeAccepted()
{
/*#ifndef QT_NO_CURSOR
    setCursor(Qt::WaitCursor);
#endif

    QString channelName = createChannelDialog->getChannelName();
    Channel channel(channelName);
    //do subscribe
    m_subscribeChannelQuery->setQuery(channel, m_session);
    m_subscribeChannelQuery->doRequest();*/
}

void downloadVideoWidget::onAddChannelAccepted()
{
/*#ifndef QT_NO_CURSOR
    setCursor(Qt::WaitCursor);
#endif

    QString name = createChannelDialog->getName();
    QString description = createChannelDialog->getDescription();
    QString url = createChannelDialog->getUrl();

    m_applyChannelQuery->setQuery(Channel(name, description, url), m_session);
    m_applyChannelQuery->doRequest();*/
}

/*void downloadVideoWidget::onRequestError(int errno)
{
    /*writeToStatusLog("Error processing "+
                     QString(this->sender()->metaObject()->className())+", errno = " +
                     QString::number(errno)+", type = " + Errno::initErrnoMap().value(errno));*/
    /*qDebug() << "Error "<< errno << " occured";
}*/


void downloadVideoWidget::onStartDownloadingVideo(QString pathToVideoFile)
{
    // -- ftp server --
    FtpDialog ftpDialog(this, pathToVideoFile);
    if (ftpDialog.exec())
    {
        ftpDialog.getUrlToVideoFile();
    }

    /*channelDialog = new ChannelDialog(this);
    channelDialog->exec();*/

    // -- Login --
    loginDialog = new LoginDialog(this);
    connect(loginDialog, SIGNAL(onAccepted()), this, SLOT(onLoginAccepted()));
    loginDialog->exec();

}
