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

#include "day.h"
#include "log.h"

class StineClient : public QObject
{
    Q_OBJECT

public:
    explicit            StineClient(QObject *parent = 0);

    /**
     * @brief if successful the signal dataUpdated is triggerd
     */
    void                getData();

    /**
     * @brief if login is successful the signal gotSession is triggerd
     * @param Username user to login
     * @param Password corresponding password
     */
    void                getSession(QString Username = "", QString Password = "");

    void                setSession(QString Session);
    void                setTerminUrl(QString terminUrl);
    void                resetTerminUrl();

    void                authenticate(QString Username, QString Password);

    bool                isbusy();

signals:
    void                dataUpdated(Day* selectedDay);
    void                gotSession(QString Session);
    void                authRequiered();
    void                loginFailed();

public slots:
    void                replyFinished(QNetworkReply *Reply);

private:

    void                extractSession(QNetworkReply *Reply);
    void                extractData(QNetworkReply *Reply);


    QString               _session;
    int                   _state{0};
    bool                  _busy;
    QString               _terminUrl;
    QNetworkAccessManager _networkManager;

    static const QString    TARGETURL;
    static const QString    TERMINURL;
    static const QString    LOGINPARAMS;
    static const QRegularExpression DATAEXPRESSION;
};

#endif // STINECLIENT_H
