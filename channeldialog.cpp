#include "channeldialog.h"
#include <QVBoxLayout>

ChannelDialog::ChannelDialog(QWidget *parent) :
    QDialog(parent)
{
    m_selectButton = new QPushButton("Select/Write Tag", this);
    connect(m_selectButton, SIGNAL(clicked()), this, SLOT(accept()));

    m_channelsListWidget = new QListWidget(this);

    setLayout(new QVBoxLayout());
    layout()->addWidget(m_channelsListWidget);
    layout()->addWidget(m_selectButton);
}
