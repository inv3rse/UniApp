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

class StineClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString Log READ getLog WRITE setLog NOTIFY LogChanged)
public:
    explicit StineClient(QObject *parent = 0);
    Q_INVOKABLE void getData();
    Q_INVOKABLE void getSession(QString Username, QString Password);

    QString getLog();
    void setLog(QString Log);

signals:
    void LogChanged();

public slots:
    void replyFinished(QNetworkReply *Reply);
    void sslErrorOccured(QNetworkReply * Reply, const QList<QSslError> & Errors);

private:
    QString _debugLog;
    QString _session;
    const QUrl _targetUrl{QStringLiteral("https://www.stine.uni-hamburg.de/scripts/mgrqispi.dll")};
    QNetworkAccessManager _networkManager;

};

#endif // STINECLIENT_H
