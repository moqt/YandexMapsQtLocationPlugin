#include "qgeomapreplyyandexmaps.h"
#include <QNetworkAccessManager>
#include <QNetworkCacheMetaData>
#include <QDateTime>

QGeoMapReplyYandexmaps::QGeoMapReplyYandexmaps(QNetworkReply *reply, const QGeoTileSpec &spec, QObject *parent)
        : QGeoTiledMapReply(spec, parent),
        m_reply(reply)
{
    connect(m_reply,
            SIGNAL(finished()),
            this,
            SLOT(networkFinished()));

    connect(m_reply,
            SIGNAL(error(QNetworkReply::NetworkError)),
            this,
            SLOT(networkError(QNetworkReply::NetworkError)));
}


QNetworkReply *QGeoMapReplyYandexmaps::networkReply() const
{
    return m_reply;
}


void QGeoMapReplyYandexmaps::abort()
{
    if (!m_reply)
        return;

    m_reply->abort();
}


void QGeoMapReplyYandexmaps::networkFinished()
{
    if (!m_reply)
        return;

    if (m_reply->error() != QNetworkReply::NoError)
        return;

    setMapImageData(m_reply->readAll());
    setMapImageFormat("png");
    setFinished(true);

    m_reply->deleteLater();
    m_reply = 0;
}


void QGeoMapReplyYandexmaps::networkError(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error);
    if (!m_reply)
        return;

    setFinished(true);
    setCached(false);
    m_reply->deleteLater();
    m_reply = 0;
}
