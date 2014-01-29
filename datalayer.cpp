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

}

void DataLayer::setPassword(QString Pass)
{

}
