#include "log.h"

Log::Log(QObject *parent) :
    QObject(parent)
{
}

Log& Log::getInstance()
{
    static Log _instance;
    return _instance;
}

void Log::writeLog(QString log, int loglevel)
{
    std::cout<<log.toStdString()<<std::endl;
    _log.prepend(log);
    emit logChanged();
}

QString Log::getLog()
{
    return _log;
}

void Log::clear()
{
    _log.clear();
    emit logChanged();
}
