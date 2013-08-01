#ifndef GEOVIDEO_H
#define GEOVIDEO_H

#include <QString>
#include <QList>
#include <QGeoPositionInfo>

QTM_USE_NAMESPACE

class GeoVideo
{
public:
    QString pathVideo;
    QList <QGeoPositionInfo> geoTags;
    GeoVideo();
};

#endif // GEOVIDEO_H
