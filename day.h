#ifndef DAY_H
#define DAY_H

#include <QObject>
#include <QList>

#include "termin.h"

class Day : public QObject
{
    Q_OBJECT
public:
    explicit Day(QList<QObject*> Appointments, QString nextDay, QString prevDay, QObject *parent = 0);
    explicit Day(QObject *parent = 0);

    QList<QObject*> getAppointments();
    QString         getNextDay();
    QString         getPrevDay();
signals:

public slots:

private:
    QList<QObject*>  _appointments;
    QString         _nextDay;
    QString         _prevDay;
};

#endif // DAY_H
