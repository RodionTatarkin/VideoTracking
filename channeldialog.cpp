#include "channeldialog.h"
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QMessageBox>

ChannelDialog::ChannelDialog(QList<Channel> m_subscribedChannels, QString url, QWidget *parent) :
    QDialog(parent)
{
    m_selectButton = new QPushButton("Write Tags to geo2tag", this);
    connect(m_selectButton, SIGNAL(clicked()), this, SLOT(onSelectButton()));

    m_nameEdit = new QLineEdit(this);

    m_nameLabel = new QLabel("name", this);
    m_nameLabel->setAlignment(Qt::AlignCenter);

    m_linkLabel = new QLabel("link to file:" + url, this);
    m_linkLabel->setWordWrap(true);
    m_linkLabel->setAlignment(Qt::AlignCenter);

    m_channelsListWidget = new QListWidget(this);

    foreach (Channel s, m_subscribedChannels)
    {
        QListWidgetItem * item = new QListWidgetItem(s.getName());
        m_channelsListWidget->addItem(item);
    }
    m_channelsListWidget->setCurrentRow(0);

    setLayout(new QVBoxLayout());
    layout()->addWidget(m_channelsListWidget);
    layout()->addWidget(m_linkLabel);
    layout()->addWidget(m_nameLabel);
    layout()->addWidget(m_nameEdit);
    layout()->addWidget(m_selectButton);
}

void ChannelDialog::onSelectButton()
{
    if (m_nameEdit->text().isEmpty())
        QMessageBox::warning(this, tr("Not enough information"), tr("Not all fields are filled"));
    else
    {
#ifndef QT_NO_CURSOR
        setCursor(Qt::WaitCursor);
#endif
        setEnabled(false);
        emit(onAccepted());
    }
}

QString ChannelDialog::getName()
{
    return m_nameEdit->text();
}

QString ChannelDialog::getChannelName()
{
    return m_channelsListWidget->item(m_channelsListWidget->currentRow())->text();
}
