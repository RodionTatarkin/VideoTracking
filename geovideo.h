#ifndef GEOVIDEO_H
#define GEOVIDEO_H

#include <QString>
#include <QList>
#include <QGeoPositionInfo>

QTM_USE_NAMESPACE

class GeoVideo
{
public:
    QString pathToVideo;
    QString videoName;
    QString url;
    QList <QGeoPositionInfo> geoTags;
    QList <QString> time;
    GeoVideo();
};

#endif // GEOVIDEO_H
