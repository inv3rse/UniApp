#include "day.h"

Day::Day(QList<QObject*> Appointments, QString nextDay, QString prevDay, QObject *parent) :
    QObject(parent)
{
    _appointments   = Appointments;
    _nextDay        = nextDay;
    _prevDay        = prevDay;
}

Day::Day(QObject *parent) :
    QObject(parent)
{

}

Day::~Day()
{
    for (QObject* obj : _appointments)
    {
        delete obj;
    }
    _appointments.clear();
}


const QList<QObject *> Day::getAppointments()
{
    return _appointments;
}

QString Day::getNextDay()
{
    return _nextDay;
}

QString Day::getPrevDay()
{
    return _prevDay;
}

