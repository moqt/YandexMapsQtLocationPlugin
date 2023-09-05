#include "qgeotilefetcheryandexmaps.h"
#include "qgeomapreplyyandexmaps.h"
#include "qgeotiledmappingmanagerengineyandexmaps.h"
#include <QtLocation/private/qgeotilespec_p.h>

#include <QDebug>
#include <QSize>
#include <QDir>
#include <QUrl>
#include <QUrlQuery>
#include <QTime>
#include <QNetworkProxy>
#include <QtCore/QJsonDocument>
#include <QSslSocket>

#include <math.h>

#include <map>

QGeoTileFetcherYandexmaps::QGeoTileFetcherYandexmaps(const QVariantMap &parameters,
                                           QGeoTiledMappingManagerEngineYandexmaps *engine)
:   QGeoTileFetcher(engine),
  m_networkManager(new QNetworkAccessManager(this)),
  m_engineYandexmaps(engine),
  m_scale(2)
{
    if(parameters.contains(QStringLiteral("yandexmaps.maps.apikey")))
        m_apiKey = parameters.value(QStringLiteral("yandexmaps.maps.apikey")).toString();
    else
        m_apiKey = parameters.value(QStringLiteral("yandexmaps.apikey")).toString();

    m_userAgent = parameters.value(QStringLiteral("yandexmaps.useragent"),
                                   "Mozilla/5.0 (X11; Linux i586; rv:31.0) Gecko/20100101 Firefox/31.0").toString().toLatin1();

    m_language = parameters.value(QStringLiteral("yandexmaps.maps.language")).toString().toLatin1();
    m_scale = parameters.value(QStringLiteral("yandexmaps.maps.scale"), 2).toReal();
}


QGeoTiledMapReply *QGeoTileFetcherYandexmaps::getTileImage(const QGeoTileSpec &spec)
{
    const QString surl = getURL(spec.mapId(), spec.x(), spec.y(), spec.zoom());
    const QUrl url(surl);

    m_netRequest.setUrl(url);
    m_netRequest.setRawHeader("User-Agent", m_userAgent);

    const auto netReply = m_networkManager->get(m_netRequest);
    return new QGeoMapReplyYandexmaps(netReply, spec);
}


QString QGeoTileFetcherYandexmaps::getURL(int type, int x, int y, int zoom) const
{
    Q_UNUSED(type);
    // TODO m_apiKey in URL
    // TODO lang in url
    return QString("https://core-renderer-tiles.maps.yandex.net/tiles?l=map&projection=web_mercator&x=%1&y=%2&z=%3&scale=%4&lang=%5")
                  .arg(x).arg(y).arg(zoom).arg(m_scale).arg(m_language);
}
