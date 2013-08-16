#include "downloadvideowidget.h"
#include <QVBoxLayout>
#include "logindialog.h"
#include "channeldialog.h"
#include "ftpdialog.h"
#include <QDebug>

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
    m_addUserQuery = new AddUserQuery();
    m_availableChannelsQuery = new AvailableChannelsQuery();
    m_subscribedChannelsQuery = new SubscribedChannelsQuery();
    m_subscribeChannelQuery = new SubscribeChannelQuery();
    m_unsubscribeChannelQuery = new UnsubscribeChannelQuery();
    m_loadTagsQuery = new LoadTagsQuery();
    m_writeTagQuery = new WriteTagQuery();
    m_applyChannelQuery = new ApplyChannelQuery();


    connect(m_loginQuery,SIGNAL(success()),this, SLOT(onLoginSuccess()));
    connect(m_loginQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));

    connect(m_addUserQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));

    connect(m_loadTagsQuery,SIGNAL(success()),this, SLOT(onLoadTagsSuccess()));
    connect(m_loadTagsQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));


    connect(m_availableChannelsQuery,SIGNAL(success()),this, SLOT(onAvailableChannelsSuccess()));
    connect(m_availableChannelsQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));

    connect(m_subscribedChannelsQuery,SIGNAL(success()),this, SLOT(onSubscribedChannelsSuccess()));
    connect(m_subscribedChannelsQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));

    connect(m_subscribeChannelQuery,SIGNAL(success()),this, SLOT(onChannelActionSuccess()));
    connect(m_subscribeChannelQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));

    connect(m_unsubscribeChannelQuery,SIGNAL(success()),this, SLOT(onChannelActionSuccess()));
    connect(m_unsubscribeChannelQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));

    connect(m_applyChannelQuery,SIGNAL(success()),this, SLOT(onApplyChannelSuccess()));
    connect(m_applyChannelQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));

    connect(m_writeTagQuery, SIGNAL(success()), this, SLOT(onWriteTagSuccess()));
    connect(m_writeTagQuery,SIGNAL(errorOccured(int)),this, SLOT(onRequestError(int)));*/
}

void downloadVideoWidget::onLoginSuccess()
{
    /*qDebug() << "Recieved session token! " << m_loginQuery->getSession();

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
    ChannelDialog channelDialog(this);
    channelDialog.exec();

    /*if (m_availableChannelsQuery->getChannels().size() == 0)
        return;
    else
    {
        m_availableChannels = m_availableChannelsQuery->getChannels();
    }

    m_subscribedChannels = m_subscribedChannelsQuery->getChannels();

    //QListWidget * listWidget = ui->channelsListWidget;
    //QListWidget * subscribedListWidget = ui->subscribedListWidget;

    // Tab - channels
     /*while(listWidget->count()>0)
    {
      listWidget->takeItem(0);
    }*/

    /*foreach (Channel s, m_availableChannels){
        QListWidgetItem * item = new QListWidgetItem(s.getName());
        if (isSubscribed(s.getName())){
            item->setBackgroundColor(Qt::lightGray);
        }

        listWidget->addItem(item);
    }

    if (m_subscribedChannelsQuery->getChannels().size() == 0 ) return;

    //Tab - writeTag
    while(subscribedListWidget->count()>0)
    {
        subscribedListWidget->takeItem(0);
    }

    foreach (Channel s, m_subscribedChannels){
        subscribedListWidget->addItem(s.getName());
    }*/
}

void downloadVideoWidget::onSubscribedChannelsSuccess()
{
    /*qDebug()<<"MainWindow::onSubscribedChannelsSuccess()";

    formChannelList();*/
}


void downloadVideoWidget::onStartDownloadingVideo(QString pathToVideoFile)
{

    // -- ftp server --
    FtpDialog ftpDialog(this, pathToVideoFile);
    if (ftpDialog.exec())
    {
        ftpDialog.getUrlToVideoFile();
    }


    // -- Login --
    LoginDialog loginDialog(this);
    loginDialog.exec();
    QString login;
    QString password;
    QString email;
    login = loginDialog.getLogin();
    password = loginDialog.getPassword();
    if (loginDialog.email)
        email = loginDialog.getEmail();
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

    formChannelList();
}
