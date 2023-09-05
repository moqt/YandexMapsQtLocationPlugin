#include "qgeocodereplyyandexmaps.h"


#include <QtPositioning/QGeoCoordinate>
#include <QtPositioning/QGeoAddress>
#include <QtPositioning/QGeoLocation>
#include <QtPositioning/QGeoRectangle>

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include "QDebug"


static QGeoCoordinate constructCoordiante(const QString &strCoord) {
    QGeoCoordinate coord;
    const auto slist = strCoord.split(',');
    if (slist.size() == 2) {
        coord.setLongitude(slist[0].toDouble());
        coord.setLatitude(slist[1].toDouble());
    }
    return coord;
}


QGeoCodeReplyYandexmaps::QGeoCodeReplyYandexmaps(QNetworkReply *reply, QObject *parent)
    :   QGeoCodeReply(parent), m_reply(reply)
{
    connect(m_reply, SIGNAL(finished()), this, SLOT(networkReplyFinished()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(networkReplyError(QNetworkReply::NetworkError)));

    setLimit(1);
    setOffset(0);
}


QGeoCodeReplyYandexmaps::~QGeoCodeReplyYandexmaps()
{
    if (m_reply)
        m_reply->deleteLater();
}


void QGeoCodeReplyYandexmaps::abort()
{
    if (!m_reply)
        return;

    m_reply->abort();

    m_reply->deleteLater();
    m_reply = 0;
}


void QGeoCodeReplyYandexmaps::networkReplyFinished()
{
    qDebug() << "QGeoCodeReplyYandexmaps::networkReplyFinished()" << (m_reply ? m_reply->error() : -1);

    if (!m_reply)
        return;

    if (m_reply->error() != QNetworkReply::NoError)
        return;

    const QByteArray replyData = m_reply->read(m_reply->bytesAvailable());
    QList<QGeoLocation> locations;
    const QJsonDocument document = QJsonDocument::fromJson(replyData);

    if (document.isObject()) {
        const QJsonObject docObject = document.object();
        const auto error = docObject["error"].toString();

        if (error.isEmpty()) {
            const auto featureMember = docObject["response"].toObject()["GeoObjectCollection"].toObject()["featureMember"].toArray();
            if (featureMember.isEmpty()) {
                setError(ParseError, "ParseError");
            } else {
                for (const auto& fm : featureMember) {
                    const auto geoObject = fm.toObject()["GeoObject"].toObject();
                    QGeoLocation location;
                    QGeoAddress address;
                    address.setText(geoObject["metaDataProperty"].toObject()["GeocoderMetaData"].toObject()["text"].toString());
                    const auto description = geoObject["description"].toString();
                    address.setState(description.split(',')[0]);
                    address.setStreet(geoObject["name"].toString());

                    location.setCoordinate(constructCoordiante(geoObject["Point"].toObject()["pos"].toString()));
                    const auto envelope = geoObject["boundedBy"].toObject()["Envelope"].toObject();
                    const QGeoRectangle bb{constructCoordiante(envelope["upperCorner"].toString()),
                                           constructCoordiante(envelope["lowerCorner"].toString())};
                    location.setBoundingBox(bb);
                    location.setAddress(address);

                    locations.append(location);
                }
            }

        } else {
            qWarning() << "QGeoCodeReplyYandexmaps error:" << error << docObject["statusCode"].toInt();
            setError(CommunicationError, docObject["message"].toString());
        }
    } else {
        setError(UnknownError, "UnknownerrorError");
    }

    setLocations(locations);
    setFinished(true);

    m_reply->deleteLater();
    m_reply = 0;
}


void QGeoCodeReplyYandexmaps::networkReplyError(QNetworkReply::NetworkError error)
{
    qDebug() << "QGeoCodeReplyYandexmaps::networkReplyError:" << error;

    Q_UNUSED(error)

    if (!m_reply)
        return;

    setError(QGeoCodeReply::CommunicationError, m_reply->errorString());

    m_reply->deleteLater();
    m_reply = 0;
}
