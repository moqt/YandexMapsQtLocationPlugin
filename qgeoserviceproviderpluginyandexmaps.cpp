#include "qgeoserviceproviderpluginyandexmaps.h"
#include "qgeocodingmanagerengineyandexmaps.h"
#include "qgeotiledmappingmanagerengineyandexmaps.h"


QGeoCodingManagerEngine *QGeoServiceProviderFactoryYandexmaps::createGeocodingManagerEngine(
    const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const
{
    return new QGeoCodingManagerEngineYandexmaps(parameters, error, errorString);
}


QGeoMappingManagerEngine *QGeoServiceProviderFactoryYandexmaps::createMappingManagerEngine(
        const QVariantMap &parameters,
        QGeoServiceProvider::Error *error,
        QString *errorString) const
{
    return new QGeoTiledMappingManagerEngineYandexmaps(parameters, error, errorString);
}


QGeoRoutingManagerEngine *QGeoServiceProviderFactoryYandexmaps::createRoutingManagerEngine(
    const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const
{
    Q_UNUSED(parameters)
    Q_UNUSED(error)
    Q_UNUSED(errorString)

    return Q_NULLPTR;
}


QPlaceManagerEngine *QGeoServiceProviderFactoryYandexmaps::createPlaceManagerEngine(
    const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const
{
    Q_UNUSED(parameters)
    Q_UNUSED(error)
    Q_UNUSED(errorString)

    return Q_NULLPTR;
}
