#include "termin.h"

Q_DECLARE_METATYPE(Termin)

Termin::Termin(QString desc, QString time,QString place,QString link, QObject *parent) :
    QObject(parent)
{
    _description = desc;
    _time = time;
    _place = place;
    _infoLink = link;
}

Termin::Termin(QObject *parent) :
    QObject(parent)
{
    _description = "";
    _time = "";
    _place = "";
    _infoLink = "";
}

//necessary to declare a Metatype
Termin::Termin(const Termin &other) :
    QObject(other.parent())
{
    _description    = other._description;
    _time           = other._time;
    _place          = other._place;
    _infoLink       = other._infoLink;
}

void Termin::setDescription(const QString & desc)
{
    if (_description != desc)
    {
        _description = desc;
        emit DescriptionChanged();
    }
}

void Termin::setTime(const QString & time)
{
    if (_time != time)
    {
        _time = time;
        emit TimeChanged();
    }
}

void Termin::setPlace(const QString & place)
{
    if (_place != place)
    {
        _place = place;
        emit PlaceChanged();
    }
}

void Termin::setInfoLink(const QString & link)
{
    if (_infoLink != link)
    {
        _infoLink = link;
        emit InfoLinkChanged();
    }
}

QString Termin::getDescription()
{
    return _description;
}

QString Termin::getTime()
{
    return _time;
}

QString Termin::getPlace()
{
    return _place;
}

QString Termin::getInfoLink()
{
    return _infoLink;
}
