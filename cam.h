#ifndef CAM_H
#define CAM_H

#define DEFAULT_UPDATE_INTERVAL 45000

#include "geovideo.h"
#include <QWidget>
#include <QCamera>
#include <QCameraViewfinder>
#include <QMediaRecorder>
#include <QAudioCaptureSource>
#include <QPushButton>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QTimerEvent>
#include <QComboBox>

QTM_USE_NAMESPACE

class Cam : public QWidget
{
private:
    int updateInterval;

    QGeoPositionInfoSource * source;
    QByteArray m_device;
    QCamera * m_camera;
    QCameraViewfinder * m_viewfinder;
    QMediaRecorder * m_mediaRecorder;
    QAudioCaptureSource * m_audioCapture;
    QPushButton * m_captureButton;
    QPushButton * m_stopButton;
    QComboBox * m_updateIntervalBox;

    GeoVideo currentVideo;


    Q_OBJECT
public:
    explicit Cam(QWidget *parent = 0);
    
signals:
    void downloadVideo(GeoVideo currentVideo);
    
public slots:
    void updateRecorderState(QMediaRecorder::State state);
    void updateRecordTime();
    void displayRecorderError();
    void recordingStarted(QMediaRecorder::State state);

    void record();
    void stop();

    void selectCamera();
    void setCamera();

    void positionUpdated(QGeoPositionInfo info);

    void downloadingVideo();

    
};

#endif // CAM_H
