#include "datalayer.h"

DataLayer::DataLayer(QQmlContext* cont, QObject *parent) :
    QObject(parent)
{
    _context = cont;
    connect(&_webClient,SIGNAL(dataUpdated(QList<QObject*>)),this,SLOT(setDataModel(QList<QObject*>)));
    connect(&_webClient,SIGNAL(authRequiered()),this,SLOT(authenticate()));
    connect(&_webClient,SIGNAL(gotSession(QString)),this,SLOT(saveSession(QString)));
}


void DataLayer::loadFromClient()
{
    _webClient.getData();
}

void DataLayer::loadFromFile()
{
    std::fstream data{};
    data.open(_filename,std::ios::in);
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
    }
}

void DataLayer::setDataModel(QList<QObject*> Data)
{
    for (QObject* obj : Data)
    {
        obj->deleteLater();
    }
    _dataModel.clear();
    _dataModel.append(Data);
    _context->setContextProperty("dataModel",QVariant::fromValue(_dataModel));
}

void DataLayer::authenticate()
{
    _webClient.authenticate(_username,_password);
}

bool DataLayer::saveToFile()
{
    std::fstream file{};
    file.open(_filename,std::ios::out);
    if (file.is_open())
    {
        file<<_username.toStdString()<<"\t"<<_password.toStdString()<<"\t"<<_session.toStdString()<<"\n";
        file.close();
        return true;
    }
    return false;
}

QList<QObject*>* DataLayer::getDataModel()
{
    return &_dataModel;
}

void DataLayer::setUsername(QString User)
{
    _username = User;
}

void DataLayer::setPassword(QString Pass)
{
    _password = Pass;
}

void DataLayer::saveSession(QString Session)
{
    _session = Session;
    saveToFile();
}
