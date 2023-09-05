#ifndef QGEOTILEDMAPPINGMANAGERENGINEYANDEXMAPS_H
#define QGEOTILEDMAPPINGMANAGERENGINEYANDEXMAPS_H

#include "QtLocation/private/qgeotiledmappingmanagerengine_p.h"
#include <QtPositioning/QGeoRectangle>

#include <QGeoServiceProvider>


class QGeoTiledMappingManagerEngineYandexmaps : public QGeoTiledMappingManagerEngine
{
    Q_OBJECT

public:
    QGeoTiledMappingManagerEngineYandexmaps(const QVariantMap &parameters,
                                       QGeoServiceProvider::Error *error,
                                       QString *errorString);

    QGeoMap *createMap() override;

private:    
    QString m_cacheDirectory;
};

#endif // QGEOTILEDMAPPINGMANAGERENGINEYANDEXMAPS_H
