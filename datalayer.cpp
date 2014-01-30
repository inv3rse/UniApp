#include "datalayer.h"

const std::string DataLayer::_USERFILE= "UserInfo";
const std::string DataLayer::_DATAFILE= "UserData";


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

bool DataLayer::saveUserToFile()
{
    std::fstream file{};
    file.open(_USERFILE,std::ios::out);
    if (file.is_open())
    {
        file<<_username.toStdString()<<"\t"<<_password.toStdString()<<"\t"<<_session.toStdString()<<"\n";
        file.close();
        return true;
    }
    return false;
}

bool DataLayer::saveDataToFile()
{
    std::fstream file{};
    file.open(_DATAFILE,std::ios::out);
    if (file.is_open())
    {
        for (QObject* obj : _dataModel)
        {
            StineData* data = qobject_cast<StineData*>(obj);
            file<<data->getDescription().toStdString()<<"\t"<<data->getTime().toStdString()<<"\t"<<data->getPlace().toStdString()<<"\t"<<data->getInfoLink().toStdString()<<std::endl;
        }
        return true;
    }
    return false;
}

void DataLayer::loadDataFromFile()
{
    QFile file(QString::fromStdString(_DATAFILE));
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

void DataLayer::loadUserFromFile()
{
    std::fstream data{};
    data.open(_USERFILE,std::ios::in);
    if(data.is_open())
    {
        if(!data.eof())
        {
            std::string username,password,session;
            data>>username>>password>>session;
            _username=QString::fromStdString(username);
            _password=QString::fromStdString(password);
            _session=QString::fromStdString(session);
        }
        data.close();
        Log::getInstance().writeLog(_username+" "+_password);
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
