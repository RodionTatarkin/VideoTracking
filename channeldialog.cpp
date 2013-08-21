#include "channeldialog.h"
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QMessageBox>

ChannelDialog::ChannelDialog(/*QList<Channel> m_subscribedChannels,*/ QWidget *parent) :
    QDialog(parent)
{
    m_selectButton = new QPushButton("Write Tag", this);
    connect(m_selectButton, SIGNAL(clicked()), this, SLOT(onSelectButton()));

    m_nameEdit = new QLineEdit(this);

    m_longitudeEdit = new QLineEdit(this);

    m_latatitudeEdit = new QLineEdit(this);

    m_nameLabel = new QLabel("name", this);
    m_nameLabel->setAlignment(Qt::AlignCenter);

    m_longitudeLabel = new QLabel("longitude", this);
    m_longitudeLabel->setAlignment(Qt::AlignCenter);

    m_latatitudeLabel = new QLabel("latatitude", this);
    m_latatitudeLabel->setAlignment(Qt::AlignCenter);

    m_channelsListWidget = new QListWidget(this);

    /*foreach (Channel s, m_subscribedChannels)
    {
        QListWidgetItem * item = new QListWidgetItem(s.getName());
        listWidget->addItem(item);
    }*/
    //m_channelsListWidget->setCurrentRow(1);

    setLayout(new QVBoxLayout());
    layout()->addWidget(m_channelsListWidget);
    layout()->addWidget(m_nameLabel);
    layout()->addWidget(m_nameEdit);
    layout()->addWidget(m_longitudeLabel);
    layout()->addWidget(m_longitudeEdit);
    layout()->addWidget(m_latatitudeLabel);
    layout()->addWidget(m_latatitudeEdit);
    layout()->addWidget(m_selectButton);
}

void ChannelDialog::onSelectButton()
{
    if (m_nameEdit->text().isEmpty() || m_longitudeEdit->text().isEmpty() || m_latatitudeEdit->text().isEmpty())
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

QString ChannelDialog::getLongitude()
{
    return m_longitudeEdit->text();
}

QString ChannelDialog::getLatatitude()
{
    return m_latatitudeEdit->text();
}

QString ChannelDialog::getChannelName()
{
    return m_channelsListWidget->item(m_channelsListWidget->currentRow())->text();
}
