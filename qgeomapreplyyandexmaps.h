#ifndef QGEOMAPREPLYYANDEXMAPS_H
#define QGEOMAPREPLYYANDEXMAPS_H

#include <QtNetwork/QNetworkReply>
#include <QtLocation/private/qgeotilespec_p.h>
#include <QtLocation/private/qgeotiledmapreply_p.h>
#include <QtCore/QPointer>

class QGeoMapReplyYandexmaps : public QGeoTiledMapReply
{
    Q_OBJECT

public:
    QGeoMapReplyYandexmaps(QNetworkReply *reply, const QGeoTileSpec &spec, QObject *parent = 0);

    void abort() override;

    QNetworkReply *networkReply() const;

private Q_SLOTS:
    void networkFinished();
    void networkError(QNetworkReply::NetworkError error);

private:
    QPointer<QNetworkReply> m_reply;
};

#endif
