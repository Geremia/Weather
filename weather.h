#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QImage>
#include <QDebug>

class Weather : public QObject
{
    Q_OBJECT
public:
    explicit Weather(QObject *parent = 0);

signals:
    void updateFinished(const QString &location, const QString &tmp, const QString &wind);
    void imageDownloaded(const QImage &);

public slots:
    void updateData(const QString &woeid);
    void getAttrImg();

private:
    QNetworkAccessManager *naManager;
    QNetworkReply *imgReply;
    QImage attrImg;

private slots:
    void onSSLErrors(QNetworkReply *);
    void onQueryFinished(QNetworkReply *);
};

#endif // WEATHER_H
