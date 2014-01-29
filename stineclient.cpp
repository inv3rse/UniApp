#include "stineclient.h"

StineClient::StineClient(QObject *parent) :
    QObject(parent)
{
    connect(&_networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}
void StineClient::getData()
{
    if (_session != "")
    {
        _state = 2;
        QString tmp = _terminUrl;
        QString url = _targetUrl + tmp.replace("<ID>",_session);
        QNetworkRequest Request{QUrl(url)};
        _networkManager.get(Request);
    }
    else
    {
        state = 3;
        getSession;
    }
}


void StineClient::getSession(QString Username, QString Password)
{
    _state =_state !=3? 1:3;
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

    if (_state == 1 || _state == 3)
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
            emit gotSession(_session);
            writeLog(refresh);
        }
        else
        {
            writeLog("login not successfull\n");
        }
        _debugLog="";
        if (_state != 3)
        {
            _state = 0;
        }
        else
        {
            getData();
        }
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

        QList<QObject*> data;

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

            data.push_back(new StineData(desc,time,place,link));;

//            _dataModel->append(new StineData(desc,time,place,link));

            writeLog("desc: "+ desc +"\n");
            writeLog("time: "+ time +"\n");
            writeLog("place: "+ place +"\n");
            writeLog("--------\n");
        }
//        _context->setContextProperty("dataModel",QVariant::fromValue(*_dataModel));

            emit dataUpdated(data);
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
