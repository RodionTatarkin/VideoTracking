#include "cam.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QCameraImageCapture>
#include <QPushButton>
#include <QMediaRecorder>
#include <QAudioCaptureSource>
#include <QDialog>
#include <QCommandLinkButton>
#include <QUrl>
#include <QDebug>
#include <QApplication>
#include <assert.h>
#include <QMediaService>
#include <QFileDialog>
#include <QGeoServiceProvider>
#include <QGeoPositionInfoSource>
#include <QFileDialog>
#include <QLabel>

QTM_USE_NAMESPACE

Cam::Cam(QWidget *parent) :
    QWidget(parent)
{
    QDialog * m_selectDialog;
    QList <QByteArray> cameras = QCamera::availableDevices();
    if (cameras.count() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("No Cameras are found!!!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
    else if (cameras.count() == 1)
        m_device = cameras.at(0);
    else
    {
        m_selectDialog = new QDialog(NULL);
        m_selectDialog->setLayout(new QVBoxLayout);
        foreach (QByteArray deviceName, cameras)
        {
            QCommandLinkButton * commandLinkButton = new QCommandLinkButton(QCamera::deviceDescription(deviceName), m_selectDialog);
            commandLinkButton->setProperty("deviceName", deviceName);
            connect(commandLinkButton, SIGNAL(clicked()), this, SLOT(selectCamera()));
            connect(commandLinkButton, SIGNAL(clicked()), m_selectDialog, SLOT(accept()));
            m_selectDialog->layout()->addWidget(commandLinkButton);
        }
        m_selectDialog->exec();
        delete m_selectDialog;
    }

    setCamera();

    // --Location--

    updateInterval = DEFAULT_UPDATE_INTERVAL;
    source = QGeoPositionInfoSource::createDefaultSource(this);
    source->setUpdateInterval(updateInterval);
    qDebug() << "Minimum value for update intervals" << source->minimumUpdateInterval();
    connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));

    /*QStringList infoSources;
    infoSources = QGeoPositionInfoSource::availableSources();
    qDebug() << infoSources.isEmpty();
    services = QGeoServiceProvider::availableServiceProviders();
    qDebug() << services.isEmpty();
    //qDebug << services.at(0).toStdString();
    QString str = services.at(0);
    qDebug() << str;
    QGeoServiceProvider service(services.at(0));
    //QGeoPositionInfoSource * source = QGeoPositionInfoSource::createSource(str, NULL);
    QGeoPositionInfoSource * source = QGeoPositionInfoSource::createDefaultSource(NULL);
    if (source)
    {
        qDebug() << "Source exists";
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));
        source->setUpdateInterval(10000);
        source->startUpdates();
    }*/

}

void Cam::selectCamera()
{
    m_device = QObject::sender()->property("deviceName").toByteArray();
}

void Cam::setCamera()
{
    m_camera = new QCamera(m_device);
    m_camera->setParent(this);
    //m_camera->setCaptureMode(QCamera::CaptureVideo);

    m_mediaRecorder = new QMediaRecorder(m_camera);
    connect(m_mediaRecorder, SIGNAL(stateChanged(QMediaRecorder::State)), this, SLOT(updateRecorderState(QMediaRecorder::State)));

    connect(m_mediaRecorder, SIGNAL(durationChanged(qint64)), this, SLOT(updateRecordTime()));
    connect(m_mediaRecorder, SIGNAL(error(QMediaRecorder::Error)), this, SLOT(displayRecorderError()));

    m_viewfinder = new QCameraViewfinder;
    m_viewfinder->setParent(this);
    setLayout(new QVBoxLayout);
    layout()->addWidget(m_viewfinder);

    m_captureButton = new QPushButton("Capture", this);
    layout()->addWidget(m_captureButton);
    connect(m_captureButton, SIGNAL(clicked()), this, SLOT(record()));

    m_stopButton = new QPushButton("Stop", this);
    layout()->addWidget(m_stopButton);
    connect(m_stopButton, SIGNAL(clicked()), this, SLOT(stop()));

    QHBoxLayout * layUpdateInterval = new QHBoxLayout();
    layUpdateInterval->addWidget(new QLabel("Update Interval(msec):", this));
    m_updateIntervalBox = new QComboBox(this);
    m_updateIntervalBox->addItem(QString::number(5000));
    m_updateIntervalBox->addItem(QString::number(30000));
    m_updateIntervalBox->addItem(QString::number(DEFAULT_UPDATE_INTERVAL));
    m_updateIntervalBox->addItem(QString::number(60000));
    m_updateIntervalBox->addItem(QString::number(90000));
    m_updateIntervalBox->setCurrentIndex(1);
    layUpdateInterval->addWidget(m_updateIntervalBox);

    layout()->addItem(layUpdateInterval);

    m_camera->setViewfinder(m_viewfinder);

    m_captureButton->setEnabled(true);
    m_stopButton->setEnabled(true);
    //updateRecorderState(m_mediaRecorder->state());


    connect(m_mediaRecorder, SIGNAL(stateChanged(QMediaRecorder::State)), this, SLOT(recordingStarted(QMediaRecorder::State)));

    /*QString fileName = QFileDialog::getSaveFileName();
    m_mediaRecorder->setOutputLocation(QUrl(fileName));*/
    //m_mediaRecorder->setOutputLocation(QUrl("D:\\movie.mkv"));
    //assert(m_mediaRecorder->isAvailable());
    /*assert(m_mediaRecorder->error() == QMediaRecorder::NoError);
    assert(m_mediaRecorder->state() == QMediaRecorder::StoppedState);
    connect(m_mediaRecorder, SIGNAL(error(QMediaRecorder::Error)), this, SLOT(err()));
    qDebug() << m_mediaRecorder->errorString();
    qDebug() << m_mediaRecorder->outputLocation().toString();*/
    /*if (m_mediaRecorder->setOutputLocation(QUrl::fromUserInput("myvideo.mp4")) == FALSE)
        qDebug() << m_mediaRecorder->outputLocation().toString();*/

   qDebug() << m_mediaRecorder->state();
   qDebug() << m_mediaRecorder->error();
   m_mediaRecorder->stop();
   m_mediaRecorder->record();

   qDebug() << m_camera->isCaptureModeSupported(QCamera::CaptureVideo);
   m_camera->setCaptureMode(QCamera::CaptureVideo);
   //m_camera->setCaptureMode(QCamera::CaptureStillImage);
   m_camera->start();
}

void Cam::downloadingVideo()
{
    int ret;
    QMessageBox messageBox(this);
    messageBox.setText("Would you like to download your video to the ftp server and after to geo2tag?");
    messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.setIcon(QMessageBox::Question);
    ret = messageBox.exec();
    switch(ret)
    {
    case QMessageBox::Ok:
        emit(downloadVideo(currentVideo));
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }

}

void Cam::updateRecorderState(QMediaRecorder::State state)
{
    switch (state) {
    case QMediaRecorder::StoppedState:
        m_captureButton->setEnabled(true);
        m_stopButton->setEnabled(false);
        m_updateIntervalBox->setEnabled(true);
        source->stopUpdates();
        downloadingVideo();
        break;
    case QMediaRecorder::PausedState:
        m_captureButton->setEnabled(true);
        m_stopButton->setEnabled(true);
        break;
    case QMediaRecorder::RecordingState:
        m_captureButton->setEnabled(false);
        m_stopButton->setEnabled(true);
        m_updateIntervalBox->setEnabled(false);
        source->requestUpdate();
        source->setUpdateInterval(m_updateIntervalBox->currentText().toInt());
        source->startUpdates();
        break;
    }
}


void Cam::updateRecordTime()
{
    QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
    qDebug() << str;
    //ui->statusbar->showMessage(str);
}

void Cam::record()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (fileDialog.exec() == QDialog::Accepted)
    {
        qDebug() << fileDialog.selectedFiles();
        m_mediaRecorder->setOutputLocation(QUrl::fromLocalFile(fileDialog.selectedFiles().first()));
    }
    currentVideo.videoName = fileDialog.labelText(QFileDialog::FileName);
    currentVideo.videoName = "MyVideo";
    currentVideo.pathToVideo = m_mediaRecorder->outputLocation().toString();
    currentVideo.pathToVideo = fileDialog.selectedFiles().first();
    m_mediaRecorder->record();
    updateRecordTime();
    qDebug() << m_mediaRecorder->error() << m_mediaRecorder->state();
    qDebug() << m_mediaRecorder->outputLocation();

    m_updateIntervalBox->setEnabled(false);
    source->requestUpdate();
    source->setUpdateInterval(m_updateIntervalBox->currentText().toInt());
    source->startUpdates();
}

void Cam::stop()
{
    m_mediaRecorder->stop();

    source->stopUpdates();
    qDebug() << currentVideo.geoTags << currentVideo.pathToVideo << currentVideo.videoName << currentVideo.time;
    downloadingVideo();
}

void Cam::displayRecorderError()
{
    QMessageBox::warning(this, tr("Capture error"), m_mediaRecorder->errorString());
    qDebug() << m_mediaRecorder->error() << m_mediaRecorder->errorString();
}

void Cam::recordingStarted(QMediaRecorder::State state)
{
    qDebug() << "recordingStarted";
    if(state == QMediaRecorder::RecordingState)
        qDebug() << "Recording started" << state;
    else
        qDebug() << state;
}

   //-- Location --
void Cam::positionUpdated(QGeoPositionInfo info)
{
    qDebug() << info;
    //currentVideo->geoTags.append(info);
    currentVideo.geoTags << info;
    currentVideo.time << QString::number(m_mediaRecorder->duration());
}

