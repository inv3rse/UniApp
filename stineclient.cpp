#include "stineclient.h"

const QString StineClient::TARGETURL                    = "https://www.stine.uni-hamburg.de/scripts/mgrqispi.dll";
const QString StineClient::TERMINURL                    = "?APPNAME=CampusNet&PRGNAME=SCHEDULER&ARGUMENTS=<ID>,-N000267,-A,-A,-N,-N000000000000000";
const QString StineClient::LOGINPARAMS                  = "&APPNAME=CampusNet&PRGNAME=LOGINCHECK&ARGUMENTS=clino%2Cusrname%2Cpass%2Cmenuno%2Cmenu_type%2Cbrowser%2Cplatform&clino=000000000000001&menuno=000265&menu_type=classic&browser=&platform=";
const QRegularExpression StineClient::DATAEXPRESSION    {"<td class=\"appointment\".*\\n(.*span.*\\n)?(.*i>.*\\n)?(?<time>.*)\\n(.*i>.*\\n)?(.*span.*\\n)?(.*br.*\\n)?(.*i>.*\\n)?((?<place>.*)?<br.*\\n)?(.*\\n.*\\n)?.*href=\"(?<link>.*)\".*title=\"(?<desc>.*)\""};


StineClient::StineClient(QObject *parent) :
    QObject(parent)
{
    _session="";
    _busy = false;
    _terminUrl=TERMINURL;
    connect(&_networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}
void StineClient::getData()
{
    if (!_busy)
    {
        _busy = true;
        if (_session != "")
        {
            _state = GET_DATA;
            QString tmp = _terminUrl;
            QString url = TARGETURL + tmp.replace("<ID>",_session);
            Log::getInstance().writeLog("req: "+url+"\n");
            QNetworkRequest Request{QUrl(url)};
            _networkManager.get(Request);
            Log::getInstance().writeLog("Data Reqest send\n");
        }
        else
        {
            _state = GET_SESSION_AND_DATA;
            getSession();
        }
    }
}


void StineClient::getSession(QString Username, QString Password)
{
    if (Username != "" && Password != "")
    {
        _state =_state !=GET_SESSION_AND_DATA? GET_SESSION:GET_SESSION_AND_DATA;
        _busy = true;
        QNetworkRequest Request{QUrl(TARGETURL)};
        QByteArray Data;
        Data.append("usrname=").append(Username).append("&").append("pass=").append(Password).append(LOGINPARAMS);
        _networkManager.post(Request,Data);
        Log::getInstance().writeLog(Data+"\n");
        Log::getInstance().writeLog("Session Reqest send\n");
    }
    else
    {
        _busy = false;
        emit authRequiered();
    }
}


void StineClient::replyFinished(QNetworkReply *Reply)
{
    Reply->deleteLater();
    if (Reply->error()!=QNetworkReply::NoError)
    {
        Log::getInstance().writeLog(Reply->errorString()+"\n");
        _state = READY;
        _busy = false;
        emit networkerror();
        return;
    }

    if (_state == GET_SESSION || _state == GET_SESSION_AND_DATA)
    {
        extractSession(Reply);
    }

    else if (_state == GET_DATA )
    {
        extractData(Reply);
    }
}


void StineClient::extractSession(QNetworkReply *Reply)
{
    if (Reply->hasRawHeader("refresh"))
    {
        Log::getInstance().writeLog("login successfull\n");
        QByteArray refresh = Reply->rawHeader("refresh");
        int start, end;
        start = refresh.indexOf("ARGUMENT") + 10;
        refresh = refresh.mid(start);
        end = refresh.indexOf(",");
        refresh = refresh.left(end);
        _session = refresh;
        emit gotSession(_session);
        Log::getInstance().writeLog(refresh+"\n");
    }
    else
    {
        Log::getInstance().writeLog("login not successfull");
        Log::getInstance().writeLog("Check Username and Password\n");

        for (auto pair : Reply->rawHeaderPairs())
        {
            Log::getInstance().writeLog(pair.first+" : "+pair.second+"\n");
        }

        _terminUrl = TERMINURL;
        _state = READY;
        _busy = false;
        emit loginFailed();

        return;
    }

    if (_state != GET_SESSION_AND_DATA)
    {
        _state = READY;
        _busy = false;
    }
    else
    {
        getData();
    }
}


void StineClient::extractData(QNetworkReply *Reply)
{
    if (!DATAEXPRESSION.isValid())
    {
        Log::getInstance().writeLog("regular expr is invalid \n");
    }

    QByteArray htmlData = Reply->readAll();

    if (htmlData.contains("Zugang verweigert") || htmlData.contains("<h1>Timeout!</h1>"))
    {
        Log::getInstance().writeLog("Session invalid, Access denied\n");
        Log::getInstance().writeLog("Updating Session...\n");
        _state = GET_SESSION_AND_DATA;
        getSession();
    }

    QString before;
    QString next;
    QList<QObject*> data;

    QRegularExpressionMatchIterator j = QRegularExpression("href=\"/scripts/mgrqispi.dll(?<before>.*)\".title.*skipLeft").globalMatch(htmlData);
    if (j.hasNext())
    {
        QRegularExpressionMatch match = j.next();
        before = match.captured("before");
    }

    QRegularExpressionMatchIterator k = QRegularExpression("href=\"/scripts/mgrqispi.dll(?<next>.*)\".title.*skipRight").globalMatch(htmlData);
    if (k.hasNext())
    {
        QRegularExpressionMatch match = k.next();
        next = match.captured("next");
    }

    next = next.replace("&amp;","&");
    before = before.replace("&amp;","&");

    Log::getInstance().writeLog("before: "+ before +"\n");
    Log::getInstance().writeLog("next: "+ next +"\n");

    QRegularExpressionMatchIterator i = DATAEXPRESSION.globalMatch(htmlData);

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

        data.push_back(new Termin(desc,time,place,link));

        Log::getInstance().writeLog("desc: "+ desc +"\n");
        Log::getInstance().writeLog("time: "+ time +"\n");
        Log::getInstance().writeLog("place: "+ place +"\n");
        Log::getInstance().writeLog("--------\n");
    }
    emit dataUpdated(new Day(data,next,before));
    _busy = false;
}


bool StineClient::isbusy()
{
    return _busy;
}

void StineClient::setTerminUrl(QString terminUrl)
{
    _terminUrl = terminUrl;
}

void StineClient::resetTerminUrl()
{
    _terminUrl = TERMINURL;
}

void StineClient::setSession(QString Session)
{
    _session = Session;
}

void StineClient::authenticate(QString Username, QString Password)
{
    getSession(Username,Password);
}
