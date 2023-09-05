#include "qgeocodingmanagerengineyandexmaps.h"
#include "qgeocodereplyyandexmaps.h"

#include <QtCore/QVariantMap>
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
#include <QtCore/QLocale>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtPositioning/QGeoCoordinate>
#include <QtPositioning/QGeoAddress>
#include <QtPositioning/QGeoShape>
#include <QtPositioning/QGeoRectangle>


static QString addressToQuery(const QGeoAddress &address)
{
    return address.street() + QStringLiteral(",+") +
            address.district() + QStringLiteral(",+") +
            address.city() + QStringLiteral(",+") +
            address.state() + QStringLiteral(",+") +
            address.country();
}


static QString coordinateToQuery(const QGeoCoordinate &coordinate)
{
    return QString::number(coordinate.longitude()) + QStringLiteral(",") +
           QString::number(coordinate.latitude());
}


QGeoCodingManagerEngineYandexmaps::QGeoCodingManagerEngineYandexmaps(const QVariantMap &parameters,
                                                                     QGeoServiceProvider::Error *error,
                                                                     QString *errorString)
    :   QGeoCodingManagerEngine(parameters), m_networkManager(new QNetworkAccessManager(this))
{
    if (parameters.contains(QStringLiteral("yandexmaps.useragent")))
        m_userAgent = parameters.value(QStringLiteral("yandexmaps.useragent")).toString().toLatin1();
    else
        m_userAgent = "Qt Location based application";

    if(parameters.contains((QStringLiteral("yandexmaps.geocode.apikey"))))
        m_apiKey = parameters.value(QStringLiteral("yandexmaps.geocode.apikey")).toString();
    else
        m_apiKey = parameters.value(QStringLiteral("yandexmaps.apikey")).toString();

    m_urlPrefix = QStringLiteral("https://geocode-maps.yandex.ru/1.x");

    *error = QGeoServiceProvider::NoError;
    errorString->clear();
}


QGeoCodeReply *QGeoCodingManagerEngineYandexmaps::geocode(const QGeoAddress &address, const QGeoShape &bounds)
{
    return geocode(addressToQuery(address), -1, -1, bounds);
}


QGeoCodeReply *QGeoCodingManagerEngineYandexmaps::geocode(const QString &address, int limit, int offset, const QGeoShape &bounds)
{
    Q_UNUSED(offset)
    Q_UNUSED(limit)

    QNetworkRequest request;
    request.setRawHeader("User-Agent", m_userAgent);

    QUrl url(m_urlPrefix);
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("geocode"), address);
    query.addQueryItem(QStringLiteral("apikey"), m_apiKey);
    query.addQueryItem(QStringLiteral("format"), QStringLiteral("json"));
    if (bounds.isValid() && !bounds.isEmpty() && bounds.type() != QGeoShape::UnknownType) {
        if (bounds.type() == QGeoShape::RectangleType) {
            const QGeoRectangle &r = static_cast<const QGeoRectangle&>(bounds);
            query.addQueryItem(QStringLiteral("bbox"),
                               (coordinateToQuery(r.topRight()) + "~" + coordinateToQuery(r.bottomLeft())));
        }
    }
    url.setQuery(query);
    request.setUrl(url);

    QNetworkReply *reply = m_networkManager->get(request);

    QGeoCodeReplyYandexmaps *geocodeReply = new QGeoCodeReplyYandexmaps(reply, this);

    connect(geocodeReply, SIGNAL(finished()), this, SLOT(replyFinished()));
    connect(geocodeReply, SIGNAL(error(QGeoCodeReply::Error,QString)),
            this, SLOT(replyError(QGeoCodeReply::Error,QString)));

    return geocodeReply;
}


QGeoCodeReply *QGeoCodingManagerEngineYandexmaps::reverseGeocode(const QGeoCoordinate &coordinate,
                                                                 const QGeoShape &bounds)
{
    qDebug() << "QGeoCodingManagerEngineYandexmaps::reverseGeocode:" << coordinateToQuery(coordinate) << m_apiKey;

    Q_UNUSED(bounds)

    QNetworkRequest request;
    request.setRawHeader("User-Agent", m_userAgent);

    QUrl url(m_urlPrefix);
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("geocode"), coordinateToQuery(coordinate));
    query.addQueryItem(QStringLiteral("apikey"), m_apiKey);
    query.addQueryItem(QStringLiteral("format"), QStringLiteral("json"));

    url.setQuery(query);
    request.setUrl(url);

    QNetworkReply *reply = m_networkManager->get(request);

    QGeoCodeReplyYandexmaps *geocodeReply = new QGeoCodeReplyYandexmaps(reply, this);

    connect(geocodeReply, SIGNAL(finished()), this, SLOT(replyFinished()));
    connect(geocodeReply, SIGNAL(error(QGeoCodeReply::Error,QString)),
            this, SLOT(replyError(QGeoCodeReply::Error,QString)));

    return geocodeReply;
}


void QGeoCodingManagerEngineYandexmaps::replyFinished()
{
    QGeoCodeReply *reply = qobject_cast<QGeoCodeReply *>(sender());
    if (reply)
        emit finished(reply);
}


void QGeoCodingManagerEngineYandexmaps::replyError(QGeoCodeReply::Error errorCode, const QString &errorString)
{
    QGeoCodeReply *reply = qobject_cast<QGeoCodeReply *>(sender());
    if (reply)
        emit error(reply, errorCode, errorString);
}
