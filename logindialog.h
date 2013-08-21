#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

class LoginDialog : public QDialog
{
    Q_OBJECT

    QLabel * m_labelLogin;
    QLabel * m_labelPassword;
    QLabel * m_labelEmail;

    QLineEdit * m_loginEdit;
    QLineEdit * m_passwordEdit;
    QLineEdit * m_emailEdit;

    QPushButton * m_userActionButton;

    QCheckBox * m_registerCheckBox;

public:
    explicit LoginDialog(QWidget *parent = 0);

    bool email;

    QString getLogin();
    QString getPassword();
    QString getEmail();
    
signals:
    void onAccepted();
    
private slots:
    void onRegisterCheckBox(int state);
    void onUserActionButton();
    
};

#endif // LOGINDIALOG_H
