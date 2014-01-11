#include "stineclient.h"

StineClient::StineClient(QObject *parent) :
    QObject(parent)
{
    connect(&_networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
//    connect(&_networkManager,SIGNAL(sslErrors(QNetworkReply * reply, const QList<QSslError> & errors)),this,SLOT(sslErrorOccured(QNetworkReply*,QList<QSslError>)));
}
void StineClient::getData()
{

}

void StineClient::getSession(QString Username, QString Password)
{
    QString Session;
    QNetworkRequest Request{_targetUrl};
    QByteArray Data;
    Data.append("usrname=").append(Username).append("&").append("pass=").append(Password).append("&APPNAME=CampusNet&PRGNAME=LOGINCHECK&ARGUMENTS=clino%2Cusrname%2Cpass%2Cmenuno%2Cmenu_type%2Cbrowser%2Cplatform&clino=000000000000000&menuno=000000&menu_type=classic&browser=&platform=");
    setLog(Data);
    setLog("\n");
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

    for (auto header: Reply->rawHeaderList())
    {
        setLog(header);
        setLog(": ");
        setLog(Reply->rawHeader(header));
        setLog("\n");
    }

    Reply->deleteLater();
    _debugLog="";
}


void StineClient::sslErrorOccured(QNetworkReply * Reply, const QList<QSslError> & Errors)
{
//    for (int i = 0; i < Errors.size(); ++i)
//    {
//        Errors.at(i).errorString();
//    }
    setLog("ssl Error Occured");
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
