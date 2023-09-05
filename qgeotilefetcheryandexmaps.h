#ifndef QGEOTILEFETCHERYANDEXMAPS_H
#define QGEOTILEFETCHERYANDEXMAPS_H

#include "qgeotiledmappingmanagerengineyandexmaps.h"

#include <QtLocation/private/qgeotilefetcher_p.h>
#include <QPointer>
#include <QNetworkReply>


class QGeoTiledMapReply;
class QGeoTileSpec;
class QGeoTiledMappingManagerEngine;
class QGeoTiledMappingManagerEngineYandexmaps;
class QNetworkAccessManager;

class QGeoTileFetcherYandexmaps : public QGeoTileFetcher
{
    Q_OBJECT

public:
    QGeoTileFetcherYandexmaps(const QVariantMap &parameters, QGeoTiledMappingManagerEngineYandexmaps *engine);

    QGeoTiledMapReply *getTileImage(const QGeoTileSpec &spec) override;

private:
    QNetworkAccessManager *m_networkManager;

    QPointer<QGeoTiledMappingManagerEngineYandexmaps> m_engineYandexmaps;
    QString m_apiKey;

    QByteArray      m_userAgent;
    QString         m_language;
    qreal           m_scale;

    QNetworkRequest m_netRequest;

    QString getURL(int type, int x, int y, int zoom) const;
};

#endif
