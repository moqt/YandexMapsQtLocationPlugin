#include "QtLocation/private/qgeocameracapabilities_p.h"
#include "qgeotiledmappingmanagerengineyandexmaps.h"
#include "qgeotiledmapyandexmaps.h"
#include "qgeotilefetcheryandexmaps.h"
#include "QtLocation/private/qgeofiletilecache_p.h"

#include <QDebug>
#include <QDir>
#include <QVariant>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/qmath.h>
#include <QtCore/qstandardpaths.h>


QGeoTiledMappingManagerEngineYandexmaps::QGeoTiledMappingManagerEngineYandexmaps(const QVariantMap &parameters,
    QGeoServiceProvider::Error *error,
    QString *errorString)
    : QGeoTiledMappingManagerEngine()
{
    Q_UNUSED(error);
    Q_UNUSED(errorString);

    const int tile = parameters.value(QStringLiteral("yandexmaps.maps.tilesize"), 256).toInt();
    setTileSize(QSize(tile, tile));

    QGeoCameraCapabilities capabilities;
    capabilities.setMinimumZoomLevel(0.0);
    capabilities.setMaximumZoomLevel(21.0);
    capabilities.setSupportsBearing(true);
    capabilities.setSupportsTilting(true);
    capabilities.setMinimumTilt(0);
    capabilities.setMaximumTilt(80);
    capabilities.setTileSize(tile);

    setCameraCapabilities(capabilities);

    QList<QGeoMapType> types;
    types << QGeoMapType(QGeoMapType::StreetMap, tr("Road Map"), tr("Normal map view in daylight mode"), false, false, 1, "yandexmaps", capabilities, parameters);
    setSupportedMapTypes(types);

    QGeoTileFetcherYandexmaps *fetcher = new QGeoTileFetcherYandexmaps(parameters, this);
    setTileFetcher(fetcher);

    if (parameters.contains(QStringLiteral("yandexmaps.cachefolder")))
        m_cacheDirectory = parameters.value(QStringLiteral("yandexmaps.cachefolder")).toString().toLatin1();

    const int szCache = 100 * 1024 * 1024;
    if (m_cacheDirectory.isEmpty())
        m_cacheDirectory = QAbstractGeoTileCache::baseCacheDirectory() + QLatin1String("yandexmaps");
    QAbstractGeoTileCache *tileCache = new QGeoFileTileCache(m_cacheDirectory);
    tileCache->setMaxDiskUsage(szCache);
    setTileCache(tileCache);

    *error = QGeoServiceProvider::NoError;
    errorString->clear();
}


QGeoMap *QGeoTiledMappingManagerEngineYandexmaps::createMap()
{
    return new QGeoTiledMapYandexmaps(this);
}

