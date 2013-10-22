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
#include <QProgressDialog>

class FtpDialog : public QDialog
{
    Q_OBJECT

    QLabel * ftpServerLabel;
    QLineEdit * ftpServerLineEdit;
    QLabel * statusLabel;
    QTreeWidget * fileList;
    QPushButton * cdToParentButton;
    QPushButton * connectButton;
    QPushButton * uploadButton;
    QPushButton * quitButton;
    //QDialogButtonBox * buttonBox;
    QProgressDialog * progressDialog;

    QHash<QString, bool> isDirectory;
    QString currentPath;
    QString ftpUrl;
    QFtp * ftp;
    QFile * file;

    QNetworkSession * networkSession;

    QString m_pathToVideoFile;
    QString m_videoFileName;

public:
    explicit FtpDialog(QWidget *parent = 0, QString pathToVideoFile = 0, QString videoFileName = 0);

    QString getUrlToVideoFile();
    
signals:
    
private slots:
    void enableConnectButton();

    //void enableDownloadButton();

    void onConnectOrDisconnect();

    void ftpCommandFinished(int commandId, bool error);
    void addToList(const QUrlInfo &urlInfo);
    void updateDataTransferProgress(qint64 readBytes, qint64 totalBytes);

    void processItem(QTreeWidgetItem * item, int column);

    void uploadFile();

    void cdToParent();
    
};

#endif // FTPDIALOG_H
