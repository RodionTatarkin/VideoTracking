#include "logindialog.h"
#include <assert.h>
#include <QVBoxLayout>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    m_labelLogin = new QLabel("Login", this);
    m_labelLogin->setAlignment(Qt::AlignCenter);
    m_labelPassword = new QLabel("Password", this);
    m_labelPassword->setAlignment(Qt::AlignCenter);
    m_labelEmail = new QLabel("Email", this);
    m_labelEmail->setAlignment(Qt::AlignCenter);

    m_loginEdit = new QLineEdit(this);
    m_passwordEdit = new QLineEdit(this);
    m_emailEdit = new QLineEdit(this);
    m_emailEdit->setEnabled(false);
    email = false;

    m_userActionButton = new QPushButton("Login", this);

    m_registerCheckBox = new QCheckBox("Register new User", this);
    m_registerCheckBox->setChecked(false);
    connect(m_registerCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onRegisterCheckBox(int)));


    setLayout(new QVBoxLayout());
    layout()->addWidget(m_labelLogin);
    layout()->addWidget(m_loginEdit);
    layout()->addWidget(m_labelPassword);
    layout()->addWidget(m_passwordEdit);
    layout()->addWidget(m_labelEmail);
    layout()->addWidget(m_registerCheckBox);
    layout()->addWidget(m_emailEdit);
    layout()->addWidget(m_userActionButton);

    m_userActionButton->setDefault(true);
    //m_userActionButton->setFocus();
    m_userActionButton->setAutoDefault(true);
    connect(m_userActionButton, SIGNAL(clicked()), this, SLOT(accept()));
}

QString LoginDialog::getLogin()
{
    return m_loginEdit->text();
}

QString LoginDialog::getPassword()
{
    return m_passwordEdit->text();
}

QString LoginDialog::getEmail()
{
    if (m_registerCheckBox->isChecked())
    {
        assert(email == true);
        return m_emailEdit->text();
    }
    else
    {
        assert(email == false);
        return QString();
    }
}


void LoginDialog::onRegisterCheckBox(int state)
{
    if (m_registerCheckBox->isChecked())
    {
        m_userActionButton->setText("Register");
        m_emailEdit->setEnabled(true);
        email = true;
    }
    else
    {
        m_userActionButton->setText("Login");
        m_emailEdit->setEnabled(false);
        email = false;
    }
}
