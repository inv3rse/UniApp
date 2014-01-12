#include "stinedata.h"

StineData::StineData(QString desc, QString time,QString place,QString link, QObject *parent) :
    QObject(parent)
{
    _description = desc;
    _time = time;
    _place = place;
    _infoLink = link;
}

void StineData::setDescription(const QString & desc)
{
    if (_description != desc)
    {
        _description = desc;
        emit DescriptionChanged();
    }
}

void StineData::setTime(const QString & time)
{
    if (_time != time)
    {
        _time = time;
        emit TimeChanged();
    }
}

void StineData::setPlace(const QString & place)
{
    if (_place != place)
    {
        _place = place;
        emit PlaceChanged();
    }
}

void StineData::setInfoLink(const QString & link)
{
    if (_infoLink != link)
    {
        _infoLink = link;
        emit InfoLinkChanged();
    }
}

QString StineData::getDescription()
{
    return _description;
}

QString StineData::getTime()
{
    return _time;
}

QString StineData::getPlace()
{
    return _place;
}

QString StineData::getInfoLink()
{
    return _infoLink;
}
