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


#include <QQmlContext>

#include "stinedata.h"

class StineClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString Log READ getLog WRITE writeLog NOTIFY LogChanged)
public:
    explicit StineClient(QObjectList* dataModel,QQmlContext* cont, QObject *parent = 0);
    Q_INVOKABLE void getData();
    Q_INVOKABLE void getSession(QString Username, QString Password);

    QString getLog();
    void writeLog(QString Log);

signals:
    void LogChanged();

public slots:
    void replyFinished(QNetworkReply *Reply);

private:
    QString _debugLog;
    QString _session;
    int     _state{0};
    const QString _targetUrl{"https://www.stine.uni-hamburg.de/scripts/mgrqispi.dll"};
    const QString _terminUrl{"?APPNAME=CampusNet&PRGNAME=SCHEDULER&ARGUMENTS=<ID>,-N000267,-A,-A,-N,-N000000000000000"};
    QNetworkAccessManager _networkManager;
    QObjectList* _dataModel;
    QQmlContext* _context;

};

#endif // STINECLIENT_H
