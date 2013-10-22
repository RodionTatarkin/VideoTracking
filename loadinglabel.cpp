#include "loadinglabel.h"

LoadingLabel::LoadingLabel(QWidget *parent) :
    QLabel(parent)
{
}

void LoadingLabel::setString(QString string)
{
    m_string = string;
}

void LoadingLabel::start()
{
    m_idTimer = startTimer(800);
    m_countDots = 0;
    setText(m_string + "      ");
    setAlignment(Qt::AlignCenter);
}

void LoadingLabel::stop()
{
    killTimer(m_idTimer);
    //setText(m_string);
}

void LoadingLabel::timerEvent(QTimerEvent *)
{
    QString text = m_string;
    m_countDots++;
    m_countDots = m_countDots % 4;
    for (int i = 1; i <= m_countDots; i++)
        text += " .";
    for (int i = m_countDots + 1; i < 4; i++)
        text += "  ";
    setText(text);
}
