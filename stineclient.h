#ifndef STINECLIENT_H
#define STINECLIENT_H

#include <QObject>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QAuthenticator>
#include <QUrl>

class StineClient : public QObject
{
    Q_OBJECT
public:
    explicit StineClient(QObject *parent = 0);
    void getData();
signals:

public slots:

private:
    QString getSession();

    QString _session;
    const QUrl _targetUrl{"https://www.stine.uni-hamburg.de/"};

};

#endif // STINECLIENT_H
