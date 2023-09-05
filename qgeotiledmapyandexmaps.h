#ifndef QGEOMAPYANDEXMAPS_H
#define QGEOMAPYANDEXMAPS_H

#include "QtLocation/private/qgeotiledmap_p.h"
#include <QtGui/QImage>
#include <QtCore/QPointer>

class QGeoTiledMappingManagerEngineYandexmaps;

class QGeoTiledMapYandexmaps: public QGeoTiledMap
{
Q_OBJECT
public:
    explicit QGeoTiledMapYandexmaps(QGeoTiledMappingManagerEngineYandexmaps *engine, QObject *parent = 0);

    QString getViewCopyright();
    void evaluateCopyrights(const QSet<QGeoTileSpec> &visibleTiles) override;

private:
    //QImage m_logo;
    QImage m_copyrightsSlab;
    QString m_lastCopyrightsString;
    QPointer<QGeoTiledMappingManagerEngineYandexmaps> m_engine;
};

#endif // QGEOMAPYANDEXMAPS_H
