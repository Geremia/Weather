#include "weather.h"
#include <QDebug>

Weather::Weather(QObject *parent) : QObject(parent)
{
    naManager = new QNetworkAccessManager(this);

    connect(naManager, &QNetworkAccessManager::finished, this, &Weather::onQueryFinished);
    connect(naManager, &QNetworkAccessManager::sslErrors, this, &Weather::onSSLErrors);
}

void Weather::updateData(const QString &woeid)
{

}

void Weather::getAttrImg()
{

}

void Weather::onSSLErrors(QNetworkReply *re)
{
    QList<QSslError> sslerrors;
    re->sslErrors(sslerrors);
    while (sslerrors.size()) {
        qDebug(sslerrors.front().errorString().data()->toLatin1());
        sslerrors.pop_front();
    }
}

void Weather::onQueryFinished(QNetworkReply *)
{

}
