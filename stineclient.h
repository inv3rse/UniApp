#ifndef STINECLIENT_H
#define STINECLIENT_H

#include <QObject>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
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

signals:
    void                dataUpdated(Day* selectedDay);
    void                gotSession(QString Session);
    void                authRequiered();
    void                loginFailed();
    void                networkerror();

public slots:
    void                replyFinished(QNetworkReply *Reply);

private:

    void                extractSession(QNetworkReply *Reply);
    void                extractData(QNetworkReply *Reply);
    void                checkCookie(QNetworkReply *Reply);

    enum                  States{READY,GET_COOKIE,GET_SESSION,GET_DATA,GET_SESSION_AND_DATA};

    States                _state;

    QString               _session;
    QString               _terminUrl;
    QNetworkAccessManager _networkManager;

    static const QString    COOKIEURL;
    static const QString    TARGETURL;
    static const QString    TERMINURL;
    static const QString    LOGINPARAMS;
    static const QRegularExpression DATAEXPRESSION;


};

#endif // STINECLIENT_H
