#include "weather.h"

Weather::Weather(QObject *parent) : QObject(parent)
{
    naManager = new QNetworkAccessManager(this);

    connect(naManager, &QNetworkAccessManager::finished, this, &Weather::onQueryFinished);
    connect(naManager, &QNetworkAccessManager::sslErrors, this, &Weather::onSSLErrors);
}

void Weather::updateData(const QString &woeid)
{
    QUrl url("https://query.yahooapis.com/v1/public/yql?q=select * from weather.forecast where woeid = " + woeid + "&format=json");
    QNetworkRequest req(url);
    naManager->get(req);
}

void Weather::getAttrImg()
{
    QUrl url("https://poweredby.yahoo.com/purple.png");
    QNetworkRequest req(url);
    imgReply = naManager->get(req);
}

void Weather::onSSLErrors(QNetworkReply *re)
{
    //re->ignoreSslErrors();
    qDebug() << re->errorString();
}

void Weather::onQueryFinished(QNetworkReply *re)
{
    //if ∃ an error
    if (re->error() != QNetworkReply::NoError) {
        qDebug() << re->errorString();
        re->deleteLater();
        return;
    }

    //if reply's an image
    if (re == imgReply) {
        attrImg = QImage::fromData(imgReply->readAll());
        emit imageDownloaded(attrImg);
        imgReply->deleteLater();
        return;
    }

    //if reply's JSON
    QByteArray result = re->readAll();
    re->deleteLater();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(result, &err);
    if (err.error != QJsonParseError::NoError) { //if ∃ an error
        qDebug() << err.errorString();
        return;
    }

    //otherwise
    QJsonObject obj = doc.object();
    QJsonObject res = obj.value("query").toObject().value("results").toObject().value("channel").toObject();

    QJsonObject locObj = res["location"].toObject();
    QString location;
    for(QJsonObject::ConstIterator it = locObj.constBegin(); it != locObj.constEnd(); it++) {
        location.append((*it).toString());
        if ((it + 1) != locObj.constEnd())
            location.append(", ");
    }

    QString temperature = res["item"].toObject()["condition"].toObject()["temp"].toString() + res["units"].toObject()["temperature"].toString();

    QJsonObject windObj = res["wind"].toObject();
    QString wind;
    for(QJsonObject::ConstIterator it = windObj.constBegin(); it != windObj.constEnd(); ++it) {
        wind.append(it.key());
        wind.append(": ");
        wind.append((*it).toString());
        wind.append("\n");
    }

    emit updateFinished(location, temperature, wind);
}
