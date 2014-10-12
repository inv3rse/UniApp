#include "datalayer.h"

const QString DataLayer::_USERFILE= "UserInfo";
const QString DataLayer::_DATAFILE= "UserData";


DataLayer::DataLayer(QQmlContext* cont, QObject *parent) :
    QObject(parent)
{
    _context = cont;
    _currentDay = NULL;
    _isPending = false;
    _authRequired = false;

    connect(&_webClient,SIGNAL(dataUpdated(Day*)),this,SLOT(setDataModel(Day*)));
    connect(&_webClient,SIGNAL(authRequiered()),this,SLOT(authenticationRequired()));
    connect(&_webClient,SIGNAL(loginFailed()),this,SLOT(authenticationRequired()));

    loadDataFromFile();
}


void DataLayer::loadDataFromClient(int day)
{
    setPending(true);
    if (day > 0)
    {
        _webClient.setTerminUrl(_currentDay->getNextDay());
    }
    else if(day < 0)
    {
        _webClient.setTerminUrl(_currentDay->getPrevDay());
    }
    else
    {
        _webClient.resetTerminUrl();
    }
    _webClient.getData();
}


bool DataLayer::saveDataToFile()
{
    QFile file(_DATAFILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QByteArray writeData;

    writeData.append(_currentDay->getNextDay()).append("\t").append(_currentDay->getPrevDay()).append("\n");

    for (QObject* obj : _currentDay->getAppointments())
    {
        Termin* Entry = qobject_cast<Termin*>(obj);
        writeData.append(Entry->getDescription()).append("\t").append(Entry->getTime()).append("\t").append(Entry->getPlace()).append("\t").append(Entry->getInfoLink()).append("\n");
    }

    int length = file.write(writeData);
    file.close();

    return length == -1? false:true;
}

void DataLayer::loadDataFromFile()
{
    QFile file(_DATAFILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QList<QObject*> Appointments;
    QString nextDay;
    QString prevDay;

    if(!file.atEnd())
    {
        QByteArray otherDayLine = file.readLine();
        QList<QByteArray> otherDays = otherDayLine.split('\t');

        if (otherDays.size()==2)
        {
            nextDay = otherDays.at(0);
            prevDay = otherDays.at(1);
        }
        else
        {
            return;
        }

        while (!file.atEnd())
        {
            QString desc,time,place,link;

            QByteArray line = file.readLine();
            QList<QByteArray> data = line.split('\t');

            if (data.size()>=4)
            {
                desc = QString(data.at(0));
                time = QString(data.at(1));
                place = QString(data.at(2));
                link = QString(data.at(3));

                Appointments.push_back(new Termin(desc,time,place,link));
            }
        }
    }
    setDataModel(new Day(Appointments,nextDay,prevDay));
}


QList<QObject *> DataLayer::getDataModel()
{
    return _dataModel;
}

void DataLayer::setUserAndPassword(QString username, QString password, bool save)
{
    if (_authRequired)
    {
        Log::getInstance().writeLog("authenticating...\n");
        _authRequired = false;
        emit authRequiredChanged();
        _webClient.authenticate(username, password, save);
    }
    else
    {
        _webClient.setUserAndPassword(username, password, save);
    }
}

QString DataLayer::getUsername()
{
    return _webClient.getUsername();
}

bool DataLayer::authRequired()
{
    return _authRequired;
}

bool DataLayer::isPending()
{
    return _isPending;
}

void DataLayer::setPending(bool Pending)
{
    if (_isPending != Pending)
    {
        _isPending = Pending;
        emit pendingChanged();
    }
}

void DataLayer::abortLogin()
{
    setPending(false);
    _authRequired = false;
    emit authRequiredChanged();
}


//--------------------SLOTS---------------------------

void DataLayer::authenticationRequired()
{
    if (!_authRequired)
    {
        _authRequired = true;
        emit authRequiredChanged();
    }
}

void DataLayer::setDataModel(Day* currentDay)
{
    if (_currentDay != NULL)
    {
         _currentDay->deleteLater();
    }
    _currentDay = currentDay;
    _dataModel  = _currentDay->getAppointments();
    emit dataModelChanged();

    saveDataToFile();
    setPending(false);
}
