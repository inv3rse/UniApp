#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QString>
#include <iostream>

class Log : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Log READ getLog WRITE writeLog NOTIFY logChanged)

public:
    static Log& getInstance();
    Q_INVOKABLE void writeLog(QString log,int loglevel = 0);
    Q_INVOKABLE void clear();
    QString getLog();

signals:
    void logChanged();
public slots:

private:
    explicit Log(QObject *parent = 0);

    static Log _instance;
    QString _log;
};

#endif // LOG_H
