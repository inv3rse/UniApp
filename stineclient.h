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
#include <QSettings>

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
     * @brief Loggt sich mit den aktuellem Benutzernamen und Passwort ein.
     * Stimmt der Benutzername oder das Passwort nicht wird das Signal
     * authRequiered gesendet.
     * @param Username user to login
     * @param Password corresponding password
     */
    void                getSession();
    void                setTerminUrl(QString terminUrl);
    void                resetTerminUrl();

    /**
     * @brief nach Signal authRequiered aufrufen um login daten zu setzen und weiter zu machen.
     * @param Username
     * @param Password
     * @param save
     */
    void                authenticate(QString Username, QString Password, bool save = false);

    /**
     * @brief setzt Benutzername und Passwort zum einloggen
     * @param username Benutzername
     * @param password Passwort
     * @param save Login Daten speichern
     */
    void                setUserAndPassword(const QString& username, const QString& password, bool save = false);

    /**
     * @brief Gibt den aktuellen Benutzernamen zurück
     * @return
     */
    QString             getUsername();


signals:
    void                dataUpdated(Day* selectedDay);
    void                authRequiered();
    void                loginFailed();
    void                networkerror();

public slots:
    void                replyFinished(QNetworkReply *Reply);

private:

    void                extractSession(QNetworkReply *Reply);
    void                extractData(QNetworkReply *Reply);
    void                getCookie();
    void                checkCookie(QNetworkReply *Reply);

    enum                  States{READY,GET_COOKIE,GET_SESSION,GET_DATA};

    States                _state;

    bool                  _getData;
    bool                  _hasCookie;
    QString               _session;
    QString               _terminUrl;
    QString               _username;
    QString               _password;
    QNetworkAccessManager _networkManager;

    static const QString    COOKIEURL;
    static const QString    TARGETURL;
    static const QString    TERMINURL;
    static const QString    LOGINPARAMS;
    static const QString    USER_KEY;
    static const QString    PASS_KEY;
    static const QString    SESSION_KEY;
    static const QRegularExpression DATAEXPRESSION;
};

#endif // STINECLIENT_H
