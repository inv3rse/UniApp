#ifndef STINECLIENT_H
#define STINECLIENT_H

#include <QObject>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QAuthenticator>
#include <QUrl>
#include <QByteArray>
#include <QList>
#include <QSslError>

#include <QRegularExpression>
#include <vector>

#include <QQmlContext>

#include "stinedata.h"
#include "log.h"

class StineClient : public QObject
{
    Q_OBJECT

public:
    explicit            StineClient(QObject *parent = 0);
    void                getData();
    void                getSession(QString Username = "", QString Password = "");

    void                authenticate(QString Username, QString Password);

signals:
    void                dataUpdated(QList<QObject*> Data);
    void                gotSession(QString Session);
    void                authRequiered();

public slots:
    void                replyFinished(QNetworkReply *Reply);

private:
    QString             _session;
    int                 _state{0};
    const QString       _targetUrl{"https://www.stine.uni-hamburg.de/scripts/mgrqispi.dll"};
    const QString       _terminUrl{"?APPNAME=CampusNet&PRGNAME=SCHEDULER&ARGUMENTS=<ID>,-N000267,-A,-A,-N,-N000000000000000"};
    QNetworkAccessManager _networkManager;
};

#endif // STINECLIENT_H
