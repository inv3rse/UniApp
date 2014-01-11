#include "stineclient.h"

StineClient::StineClient(QObject *parent) :
    QObject(parent)
{
    connect(&_networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}
void StineClient::getData()
{   //no wildcard support
    //appointment(.*>\n)+[\t ](.*\n){3}[\t ]+([A-z 0-9]+).*[\n\t]+.*>[\n\t]+(.*)

    _state = 2;
    QString tmp = _terminUrl;
    QString url = _targetUrl + tmp.replace("<ID>",_session);
    QNetworkRequest Request{QUrl(url)};
    _networkManager.get(Request);
}

void StineClient::getSession(QString Username, QString Password)
{
    _state = 1;
    QNetworkRequest Request{QUrl(_targetUrl)};
    QByteArray Data;
    Data.append("usrname=").append(Username).append("&").append("pass=").append(Password).append("&APPNAME=CampusNet&PRGNAME=LOGINCHECK&ARGUMENTS=clino%2Cusrname%2Cpass%2Cmenuno%2Cmenu_type%2Cbrowser%2Cplatform&clino=000000000000000&menuno=000000&menu_type=classic&browser=&platform=");
    _networkManager.post(Request,Data);
    writeLog("Reqest send\n");
}


void StineClient::replyFinished(QNetworkReply *Reply)
{
    if (Reply->error()!=QNetworkReply::NoError)
    {
        writeLog(Reply->errorString()+"\n");
        Reply->deleteLater();
        _state = 666;
        return;
    }

    if (_state == 1)
    {
        if (Reply->hasRawHeader("refresh"))
        {
            writeLog("login successfull\n");
            QByteArray refresh = Reply->rawHeader("refresh");
            int start, end;
            start = refresh.indexOf("ARGUMENT") + 10;
            refresh = refresh.mid(start);
            end = refresh.indexOf(",");
            refresh = refresh.left(end);
            _session = refresh;
            writeLog(refresh);
        }
        else
        {
            writeLog("login not successfull\n");
        }
        _debugLog="";
        _state = 0;
    }
    else if (_state ==2 )
    {
        _debugLog = "";
        QRegularExpression re("(appointment)(.*>)");
//        re.setPatternOptions(QRegularExpression::MultilineOption);
        QRegularExpressionMatch match = re.match(Reply->readAll());
        if (match.hasMatch())
        {
            writeLog("match\n");
            QString reg1 = match.captured(1);
            QString reg2 = match.captured(2);
//            QString reg3 = match.captured(3);
            writeLog(reg1+"\n");
            writeLog(reg2+"\n");
//            writeLog(reg3+"\n");
        }
        else
        {
            writeLog("does not match\n");
        }
    }


    Reply->deleteLater();
}

void StineClient::writeLog(QString Log)
{
    _debugLog  += Log;
    emit LogChanged();
}

QString StineClient::getLog()
{
    return _debugLog;
}
