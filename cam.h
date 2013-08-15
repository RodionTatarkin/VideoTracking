#ifndef CAM_H
#define CAM_H

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

QTM_USE_NAMESPACE

class Cam : public QWidget
{
private:
    QGeoPositionInfoSource * source;
    QByteArray m_device;
    QCamera * m_camera;
    QCameraViewfinder * m_viewfinder;
    QMediaRecorder * m_mediaRecorder;
    QAudioCaptureSource * m_audioCapture;
    QPushButton * m_captureButton;
    QPushButton * m_stopButton;
    int time;
    int timer;

    GeoVideo * currentVideo;


    Q_OBJECT
public:
    explicit Cam(QWidget *parent = 0);
    ~Cam();
    void timerEvent(QTimerEvent *);
    
signals:
    void downloadVideo(QString pathToVideoFile);
    
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
