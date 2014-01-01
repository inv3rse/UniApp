#include "stineclient.h"

StineClient::StineClient(QObject *parent) :
    QObject(parent)
{
    connect(&_networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}
void StineClient::getData()
{

}

void StineClient::getSession(QString Username, QString Password)
{
    QString Session;
    QNetworkRequest Request{_targetUrl};
    QByteArray Data;

    Data.append("usrname=").append(Username).append("&").append("pass=").append(Password);
    _networkManager.post(Request,Data);
    setLog("Reqest send");
}


void StineClient::replyFinished(QNetworkReply *Reply)
{
    if (Reply->error()!=QNetworkReply::NoError)
    {
        setLog(Reply->errorString()+"\n");
        Reply->deleteLater();
        return;
    }
    setLog(Reply->readAll().data());
    Reply->deleteLater();
}




void StineClient::setLog(QString Log)
{
    _debugLog  += Log;
    emit LogChanged();
}

QString StineClient::getLog()
{
    return _debugLog;
}
