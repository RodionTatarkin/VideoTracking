#ifndef FTPDIALOG_H
#define FTPDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QProgressDialog>
#include <QTreeWidget>
#include <QFtp>
#include <QHash>
#include <QFile>
#include <QNetworkSession>

class FtpDialog : public QDialog
{
    Q_OBJECT

    QLabel *ftpServerLabel;
    QLineEdit *ftpServerLineEdit;
    QLabel *statusLabel;
    QTreeWidget *fileList;
    QPushButton *cdToParentButton;
    QPushButton *connectButton;
    QPushButton *downloadButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QProgressDialog *progressDialog;

    QHash<QString, bool> isDirectory;
    QString currentPath;
    QFtp *ftp;
    QFile *file;

    QNetworkSession *networkSession;

public:
    explicit FtpDialog(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // FTPDIALOG_H
