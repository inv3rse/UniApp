#include "datalayer.h"

DataLayer::DataLayer(QQmlContext* cont, QObject *parent) :
    QObject(parent)
{
//    _webClient = StineClient{};
    _context = cont;
    connect(&_webClient,SIGNAL(dataUpdated(QList<QObject*>)),this,SLOT(setDataModel(QList<QObject*>)));
}


void DataLayer::loadFromClient()
{

}

void DataLayer::loadFromFile()
{

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

bool DataLayer::saveToFile()
{

    return 0;
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
}
