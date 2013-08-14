#ifndef CHANNELDIALOG_H
#define CHANNELDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>

class ChannelDialog : public QDialog
{
    Q_OBJECT

    QListWidget * m_channelsListWidget;
    QPushButton * m_selectButton;
    QTextEdit * m_nameEdit;
    QTextEdit *  m_latatitudeEdit;
    QTextEdit * m_longitudeEdit;

public:
    explicit ChannelDialog(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CHANNELDIALOG_H
