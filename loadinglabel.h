#ifndef LOADINGLABEL_H
#define LOADINGLABEL_H

#include <QLabel>

class LoadingLabel : public QLabel
{
    Q_OBJECT

    QString m_string;
    int m_countDots;
    int m_idTimer;

    void timerEvent(QTimerEvent *);

public:
    explicit LoadingLabel(QWidget *parent = 0);

    void setString(QString string);
    
signals:
    
public slots:
    void start();
    void stop();
    
};

#endif // LOADINGLABEL_H
