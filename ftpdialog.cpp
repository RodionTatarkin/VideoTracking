#include "ftpdialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QNetworkConfigurationManager>
#include <QSettings>
#include <QUrl>
#include <QMessageBox>

FtpDialog::FtpDialog(QWidget *parent, QString pathToVideoFile) :
    QDialog(parent)
{
    m_pathToVideoFile = pathToVideoFile;
    ftp = NULL;

    ftpServerLabel = new QLabel(tr("Ftp &server:"), this);
    ftpServerLineEdit = new QLineEdit("ftp.qt.nokia.com", this);
    ftpServerLabel->setBuddy(ftpServerLineEdit);

    statusLabel = new QLabel(tr("Please enter the name of an FTP server."), this);
    statusLabel->setWordWrap(true);

    fileList = new QTreeWidget(this);
    fileList->setEnabled(false);
    fileList->setRootIsDecorated(false);
    fileList->setHeaderLabels(QStringList() << tr("Name") << tr("Size") << tr("Owner") << tr("Group") << tr("Time"));
    fileList->header()->setStretchLastSection(false);

    connectButton = new QPushButton(tr("Connect"), this);
    connectButton->setDefault(true);

    cdToParentButton = new QPushButton(this);
    cdToParentButton->setIcon(QPixmap(":/images/cdtoparent.png"));
    cdToParentButton->setEnabled(false);

    uploadButton = new QPushButton(tr("Upload"), this);
    uploadButton->setEnabled(false);

    quitButton = new QPushButton(tr("Quit"), this);

    QHBoxLayout * buttonBoxLayout = new QHBoxLayout;
    buttonBoxLayout->addWidget(uploadButton);
    buttonBoxLayout->addWidget(quitButton);

    /*buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(uploadButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);*/

    progressDialog = new QProgressDialog(this);

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(connectButton, SIGNAL(clicked()), this, SLOT(onConnectOrDisconnect()));

    connect(fileList, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(processItem(QTreeWidgetItem*,int)));
    //connect(fileList, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(enableDownloadButton()));

    connect(uploadButton, SIGNAL(clicked()), this, SLOT(uploadFile()));

    connect(cdToParentButton, SIGNAL(clicked()), this, SLOT(cdToParent()));
            /*
    connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));*/

    QHBoxLayout * topLayout = new QHBoxLayout;
    topLayout->addWidget(ftpServerLabel);
    topLayout->addWidget(ftpServerLineEdit);
    topLayout->addWidget(cdToParentButton);
    topLayout->addWidget(connectButton);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(fileList);
    mainLayout->addWidget(statusLabel);
    //mainLayout->addWidget(buttonBox);
    mainLayout->addLayout(buttonBoxLayout);
    setLayout(mainLayout);

    QNetworkConfigurationManager manager;
    //qDebug() << manager.capabilities() << "end";
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(enableConnectButton()));

        connectButton->setEnabled(false);
        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    }

    setWindowTitle(tr("FTP"));
}

void FtpDialog::enableConnectButton()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();

    connectButton->setEnabled(networkSession->isOpen());
    statusLabel->setText(tr("Please enter the name of an FTP server."));
}

/*void FtpDialog::enableDownloadButton()
{
    QTreeWidgetItem * current = fileList->currentItem();
    if (current)
    {
        QString currentFile = current->text(0);
        uploadButton->setEnabled(!isDirectory.value(currentFile));
    } else
    {
        uploadButton->setEnabled(false);
    }
}*/

void FtpDialog::onConnectOrDisconnect()
{
    // Disconnect
    if (ftp)
    {
        ftp->abort();
        ftp->deleteLater();
        ftp = 0;

        //fileList->clear();
        fileList->setEnabled(false);
        cdToParentButton->setEnabled(false);
        uploadButton->setEnabled(false);
        connectButton->setEnabled(true);
        connectButton->setText(tr("Connect"));
#ifndef QT_NO_CURSOR
        setCursor(Qt::ArrowCursor);
#endif
        statusLabel->setText(tr("Please enter the name of an FTP server."));
        return;
    }

#ifndef QT_NO_CURSOR
    setCursor(Qt::WaitCursor);
#endif

    //Connect

    ftp = new QFtp(this);
    connect(ftp, SIGNAL(commandFinished(int, bool)),this, SLOT(ftpCommandFinished(int, bool)));
    connect(ftp, SIGNAL(listInfo(QUrlInfo)),this, SLOT(addToList(QUrlInfo)));
    connect(ftp, SIGNAL(dataTransferProgress(qint64,qint64)),this, SLOT(updateDataTransferProgress(qint64,qint64)));

    fileList->clear();
    currentPath.clear();
    isDirectory.clear();

    QUrl url(ftpServerLineEdit->text());
    if (!url.isValid() || url.scheme().toLower() != QLatin1String("ftp"))
    {
        ftp->connectToHost(ftpServerLineEdit->text(), 21);
        ftp->login();
    }
    else
    {
        ftp->connectToHost(url.host(), url.port(21));

        if (!url.userName().isEmpty())
            ftp->login(QUrl::fromPercentEncoding(url.userName().toLatin1()), url.password());
        else
            ftp->login();
        if (!url.path().isEmpty())
            ftp->cd(url.path());
    }

    fileList->setEnabled(true);
    connectButton->setEnabled(false);
    connectButton->setText(tr("Disconnect"));
    statusLabel->setText(tr("Connecting to FTP server %1...").arg(ftpServerLineEdit->text()));
}

void FtpDialog::ftpCommandFinished(int commandId, bool error)
{
/*#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
#endif*/
    if (ftp->currentCommand() == QFtp::ConnectToHost)
    {
        if (error)
        {
            QMessageBox::information(this, tr("FTP"),
                                     tr("Unable to connect to the FTP server "
                                        "at %1. Please check that the host "
                                        "name is correct.")
                                     .arg(ftpServerLineEdit->text()));
            onConnectOrDisconnect();
            return;
        }
        statusLabel->setText(tr("Logged onto %1.")
                             .arg(ftpServerLineEdit->text()));
        fileList->setFocus();
        uploadButton->setDefault(true);
        connectButton->setEnabled(true);
        return;
    }

    if (ftp->currentCommand() == QFtp::Login)
        ftp->list();

    if (ftp->currentCommand() == QFtp::List)
    {
        if (isDirectory.isEmpty())
        {
            fileList->addTopLevelItem(new QTreeWidgetItem(QStringList() << tr("<empty>")));
            fileList->setEnabled(false);
        }
        uploadButton->setEnabled(true);
    }

    if (ftp->currentCommand() == QFtp::Put)
    {
        if (error)
        {
            //qDebug() << ftp->errorString();
            statusLabel->setText(tr("Canceled download of %1.").arg(file->fileName()));
            file->close();
        }
        else
        {
            statusLabel->setText(tr("Uploaded %1 to current directory.").arg(file->fileName()));
            file->close();
        }
        delete file;
        progressDialog->hide();
    }

    /*if (ftp->currentCommand() == QFtp::Get) {
        if (error) {
            statusLabel->setText(tr("Canceled download of %1.")
                                 .arg(file->fileName()));
            file->close();
            file->remove();
        } else {
            statusLabel->setText(tr("Downloaded %1 to current directory.")
                                 .arg(file->fileName()));
            file->close();
        }
        delete file;
        enableDownloadButton();
        progressDialog->hide();
//![8]
//![9]
    } else if (ftp->currentCommand() == QFtp::List) {
        if (isDirectory.isEmpty()) {
            fileList->addTopLevelItem(new QTreeWidgetItem(QStringList() << tr("<empty>")));
            fileList->setEnabled(false);
        }
    }*/
    //![9]
}

void FtpDialog::addToList(const QUrlInfo & urlInfo)
{
    QTreeWidgetItem * item = new QTreeWidgetItem;
    item->setText(0, urlInfo.name());
    item->setText(1, QString::number(urlInfo.size()));
    item->setText(2, urlInfo.owner());
    item->setText(3, urlInfo.group());
    item->setText(4, urlInfo.lastModified().toString("MMM dd yyyy"));

    QPixmap pixmap(urlInfo.isDir() ? ":/images/dir.  png" : ":/images/file.png");
    item->setIcon(0, pixmap);

    isDirectory[urlInfo.name()] = urlInfo.isDir();
    fileList->addTopLevelItem(item);
    if (!fileList->currentItem())
    {
        fileList->setCurrentItem(fileList->topLevelItem(0));
        fileList->setEnabled(true);
    }
}

void FtpDialog::processItem(QTreeWidgetItem * item, int column)
{
    QString name = item->text(0);
    if (isDirectory.value(name))
    {
        fileList->clear();
        isDirectory.clear();
        currentPath += '/';
        currentPath += name;
        ftp->cd(name);
        ftp->list();
        cdToParentButton->setEnabled(true);
        uploadButton->setEnabled(false);
#ifndef QT_NO_CURSOR
        setCursor(Qt::WaitCursor);
#endif
        return;
    }
}

void FtpDialog::uploadFile()
{
    qDebug() << QFile::exists(m_pathToVideoFile);

    file = new QFile(m_pathToVideoFile);
    /*if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("FTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(file->errorString()));
        delete file;
        return;
    }*/

    ftp->put(file, "newFile");

    progressDialog->setLabelText(tr("Downloading %1...").arg(m_pathToVideoFile));
    uploadButton->setEnabled(false);
    progressDialog->exec();
}

void FtpDialog::cdToParent()
{
#ifndef QT_NO_CURSOR
    setCursor(Qt::WaitCursor);
#endif
    fileList->clear();
    isDirectory.clear();
    currentPath = currentPath.left(currentPath.lastIndexOf('/'));
    if (currentPath.isEmpty())
    {
        cdToParentButton->setEnabled(false);
        ftp->cd("/");
    } else
    {
        ftp->cd(currentPath);
    }
    ftp->list();
    uploadButton->setEnabled(false);
}

void FtpDialog::updateDataTransferProgress(qint64 readBytes, qint64 totalBytes)
{
}

