#ifndef QGEOCODEREPLYYANDEXMAPS_H
#define QGEOCODEREPLYYANDEXMAPS_H

#include <QtNetwork/QNetworkReply>
#include <QtLocation/QGeoCodeReply>

class QGeoCodeReplyYandexmaps : public QGeoCodeReply
{
    Q_OBJECT

public:
    explicit QGeoCodeReplyYandexmaps(QNetworkReply *reply, QObject *parent = 0);
    ~QGeoCodeReplyYandexmaps() override;

    void abort() override;

private Q_SLOTS:
    void networkReplyFinished();
    void networkReplyError(QNetworkReply::NetworkError error);

private:
    QNetworkReply *m_reply;
};

#endif // QGEOCODEREPLYORS_H
