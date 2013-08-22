#include "createchanneldialog.h"
#include <QVBoxLayout>
#include <QMessageBox>

CreateChannelDialog::CreateChannelDialog(QList<Channel> m_availableChannels, QWidget *parent) :
    QDialog(parent)
{
    m_channelsListWidget = new QListWidget(this);
    foreach (Channel s, m_availableChannels)
    {
        QListWidgetItem * item = new QListWidgetItem(s.getName());
        m_channelsListWidget->addItem(item);
    }
    m_channelsListWidget->setCurrentRow(1);

    m_subscribeButton = new QPushButton("Subscribe", this);
    connect(m_subscribeButton, SIGNAL(clicked()), this, SLOT(onSubscribeChannelButton()));

    m_channelNameLabel = new QLabel("Channel name", this);
    m_channelNameLabel->setAlignment(Qt::AlignCenter);

    m_channelNameEdit = new QLineEdit(this);

    m_descriptionLabel = new QLabel("Description", this);
    m_descriptionLabel->setAlignment(Qt::AlignCenter);

    m_descriptionEdit = new QLineEdit(this);

    m_urlLabel = new QLabel("Url", this);
    m_urlLabel->setAlignment(Qt::AlignCenter);

    m_urlEdit = new QLineEdit(this);

    m_addChannelButton = new QPushButton("Add channel", this);
    connect(m_addChannelButton, SIGNAL(clicked()), this, SLOT(onAddChannelButton()));

    setLayout(new QVBoxLayout());
    layout()->addWidget(m_channelsListWidget);
    layout()->addWidget(m_subscribeButton);
    layout()->addWidget(m_channelNameLabel);
    layout()->addWidget(m_channelNameEdit);
    layout()->addWidget(m_descriptionLabel);
    layout()->addWidget(m_descriptionEdit);
    layout()->addWidget(m_urlLabel);
    layout()->addWidget(m_urlEdit);
    layout()->addWidget(m_addChannelButton);

    m_subscribeButton->setDefault(true);
    m_addChannelButton->setDefault(true);

    setWindowTitle("geo2tag Create Channel");
}

QString CreateChannelDialog::getChannelName()
{
    return m_channelsListWidget->item(m_channelsListWidget->currentRow())->text();
}

QString CreateChannelDialog::getName()
{
    return m_channelNameEdit->text();
}

QString CreateChannelDialog::getDescription()
{
    return m_descriptionEdit->text();
}

QString CreateChannelDialog::getUrl()
{
    return m_urlEdit->text();
}

void CreateChannelDialog::onSubscribeChannelButton()
{
    setEnabled(false);
    emit(onSubscribeAccepted());
#ifndef QT_NO_CURSOR
        setCursor(Qt::WaitCursor);
#endif
}

void CreateChannelDialog::onAddChannelButton()
{
    if (m_channelNameEdit->text().isEmpty() || m_descriptionEdit->text().isEmpty() || m_urlEdit->text().isEmpty())
        QMessageBox::warning(this, tr("Not enough information"), tr("Not all fields are filled"));
    else
    {
#ifndef QT_NO_CURSOR
        setCursor(Qt::WaitCursor);
#endif
        setEnabled(false);
        emit(onAddChannelAccepted());
    }
}
