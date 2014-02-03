#include "stineclient.h"

const QString StineClient::TARGETURL    = "https://www.stine.uni-hamburg.de/scripts/mgrqispi.dll";
const QString StineClient::TERMINURL    = "?APPNAME=CampusNet&PRGNAME=SCHEDULER&ARGUMENTS=<ID>,-N000267,-A,-A,-N,-N000000000000000";
const QString StineClient::LOGINPARAMS  = "&APPNAME=CampusNet&PRGNAME=LOGINCHECK&ARGUMENTS=clino%2Cusrname%2Cpass%2Cmenuno%2Cmenu_type%2Cbrowser%2Cplatform&clino=000000000000000&menuno=000000&menu_type=classic&browser=&platform=";


StineClient::StineClient(QObject *parent) :
    QObject(parent)
{
    _session="";
    connect(&_networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}
void StineClient::getData()
{
    if (_session != "")
    {
        _state = 2;
        QString tmp = TERMINURL;
        QString url = TARGETURL + tmp.replace("<ID>",_session);
        QNetworkRequest Request{QUrl(url)};
        _networkManager.get(Request);
        Log::getInstance().writeLog("Data Reqest send\n");
    }
    else
    {
        _state = 3;
        getSession();
    }
}


void StineClient::getSession(QString Username, QString Password)
{
    if (Username != "" && Password != "")
    {
        _state =_state !=3? 1:3;
        QNetworkRequest Request{QUrl(TARGETURL)};
        QByteArray Data;
        Data.append("usrname=").append(Username).append("&").append("pass=").append(Password).append(LOGINPARAMS);
        _networkManager.post(Request,Data);
        Log::getInstance().writeLog("Session Reqest send\n");
    }
    else
    {
        emit authRequiered();
    }
}


void StineClient::replyFinished(QNetworkReply *Reply)
{
    Reply->deleteLater();
    if (Reply->error()!=QNetworkReply::NoError)
    {
        Log::getInstance().writeLog(Reply->errorString()+"\n");
        _state = 666;
        return;
    }

    if (_state == 1 || _state == 3)
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
            _state = 0;
            return;
        }

        if (_state != 3)
        {
            _state = 0;
        }
        else
        {
            getData();
        }
    }

    else if (_state == 2 )
    {
        QRegularExpression re("<td class=\"appointment\".*\\n(.*span.*\\n)?(.*i>.*\\n)?(?<time>.*)\\n(.*i>.*\\n)?(.*span.*\\n)?(.*br.*\\n)?(.*i>.*\\n)?((?<place>.*)?<br.*\\n)?(.*\\n.*\\n)?.*href=\"(?<link>.*)\".*title=\"(?<desc>.*)\"");

        if (!re.isValid())
        {
            Log::getInstance().writeLog("regular expr is invalid \n");
        }

        // Todo: check if session is invalid
        QByteArray htmlData = Reply->readAll();

        if (htmlData.contains("Zugang verweigert"))
        {
            Log::getInstance().writeLog("Session invalid, Access denied\n");
            Log::getInstance().writeLog("Updating Session...\n");
            _state = 3;
            getSession();
        }

        QList<QObject*> data;

        QRegularExpressionMatchIterator i = re.globalMatch(htmlData);
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
            emit dataUpdated(new Day(data,"",""));
    }
}

void StineClient::setSession(QString Session)
{
    _session = Session;
}

void StineClient::authenticate(QString Username, QString Password)
{
    getSession(Username,Password);
}
