#ifndef QGEOCODINGMANAGERENGINEYANDEXMAPS_H
#define QGEOCODINGMANAGERENGINEYANDEXMAPS_H

#include <QtLocation/QGeoServiceProvider>
#include <QtLocation/QGeoCodingManagerEngine>
#include <QtLocation/QGeoCodeReply>

class QNetworkAccessManager;

class QGeoCodingManagerEngineYandexmaps : public QGeoCodingManagerEngine
{
    Q_OBJECT

public:
    QGeoCodingManagerEngineYandexmaps(const QVariantMap &parameters, QGeoServiceProvider::Error *error,
                               QString *errorString);

    QGeoCodeReply *geocode(const QGeoAddress &address, const QGeoShape &bounds) Q_DECL_OVERRIDE;
    QGeoCodeReply *geocode(const QString &address, int limit, int offset,
                           const QGeoShape &bounds) Q_DECL_OVERRIDE;
    QGeoCodeReply *reverseGeocode(const QGeoCoordinate &coordinate,
                                  const QGeoShape &bounds) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void replyFinished();
    void replyError(QGeoCodeReply::Error errorCode, const QString &errorString);

private:
    QNetworkAccessManager *m_networkManager;
    QByteArray m_userAgent;
    QString m_urlPrefix;
    QString m_apiKey;
};

#endif // QGEOCODINGMANAGERENGINEOrs_H
