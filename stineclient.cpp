#include "stineclient.h"

StineClient::StineClient(QObjectList* dataModel,QQmlContext* cont, QObject *parent) :
    QObject(parent)
{
    _dataModel = dataModel;
    _context = cont;
    connect(&_networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}
void StineClient::getData()
{
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
        writeLog("processing...");
        _debugLog = "";
        //<td class=\"appointment\".*\\n(.*span.*\\n)?(?<time>.*)
        QRegularExpression re("<td class=\"appointment\".*\\n(.*span.*\\n)?(?<time>.*)\\n(.*span.*\\n)?(.*br.*\\n)?((?<place>.*)<br.*\\n)?.*href=\"(?<link>.*)\n(?<desc>.*)");

        if (!re.isValid())
        {
            writeLog("regular expr is invalid \n");
        }

        QRegularExpressionMatchIterator i = re.globalMatch(Reply->readAll());
        while (i.hasNext())
        {
            QString desc,time,place,link;
            QRegularExpressionMatch match = i.next();
            desc = match.captured("desc");
            desc = desc.trimmed();
            time = match.captured("time");
            time = time.trimmed();
            place = match.captured("place");
            place = place.trimmed();
            link = match.captured("link");

            _dataModel->append(new StineData(desc,time,place,link));

            writeLog("desc: "+ desc +"\n");
            writeLog("time: "+ time +"\n");
            writeLog("place: "+ place +"\n");
            writeLog("--------\n");
        }
        _context->setContextProperty("dataModel",QVariant::fromValue(*_dataModel));
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
