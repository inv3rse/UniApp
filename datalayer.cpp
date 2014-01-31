#include "datalayer.h"

const QString DataLayer::_USERFILE= "UserInfo";
const QString DataLayer::_DATAFILE= "UserData";


DataLayer::DataLayer(QQmlContext* cont, QObject *parent) :
    QObject(parent)
{
    _context = cont;

    connect(&_webClient,SIGNAL(dataUpdated(QList<QObject*>)),this,SLOT(setDataModel(QList<QObject*>)));
    connect(&_webClient,SIGNAL(authRequiered()),this,SLOT(authenticate()));
    connect(&_webClient,SIGNAL(gotSession(QString)),this,SLOT(saveSession(QString)));

    loadUserFromFile();
    loadDataFromFile();
}


void DataLayer::loadDataFromClient()
{
    _webClient.getData();
}


bool DataLayer::saveDataToFile()
{
    QFile file(_DATAFILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QByteArray writeData;
    for (QObject* obj : _dataModel)
    {
        StineData* Entry = qobject_cast<StineData*>(obj);
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

    QList<QObject*> Entry;
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

            Entry.push_back(new StineData(desc,time,place,link));
        }
    }
    setDataModel(Entry);
}


bool DataLayer::saveUserToFile()
{
    QFile file(_USERFILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QByteArray writeData;

    writeData.append(_username).append("\t").append(_password).append("\t").append(_session).append("\n");

    int length = file.write(writeData);
    file.close();

    return length == -1? false:true;
}

void DataLayer::loadUserFromFile()
{

    QFile file(_USERFILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray line = file.readLine();
    file.close();
    QList<QByteArray> data = line.split('\t');

    if (data.size()>=3)
    {
        _username = QString(data.at(0));
        _password = QString(data.at(1));
        _session  = QString(data.at(2));
    }
}

QList<QObject*> DataLayer::getDataModel()
{
    return _dataModel;
}

void DataLayer::setUsername(QString User)
{
    _username = User;
}

void DataLayer::setPassword(QString Pass)
{
    _password = Pass;
}



//--------------------SLOTS---------------------------

void DataLayer::authenticate()
{
    if (_username!="" && _password!="")
    {
        Log::getInstance().writeLog("authenticating...\n");
        _webClient.authenticate(_username,_password);
    }
}

void DataLayer::loginFailed()
{
    //TODO: implementation
}

void DataLayer::setDataModel(QList<QObject*> Data)
{
    for(QObject* obj : _dataModel)
    {
        obj->deleteLater();
    }
    _dataModel.clear();
    _dataModel.append(Data);
    saveDataToFile();
    _context->setContextProperty("dataModel",QVariant::fromValue(_dataModel));
}

void DataLayer::saveSession(QString Session)
{
    _session = Session;
    saveUserToFile();
}
