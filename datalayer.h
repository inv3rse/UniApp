#ifndef DATALAYER_H
#define DATALAYER_H

#include <QObject>
#include <QString>
#include <string>
#include <QQmlContext>
#include <fstream>
#include "stineclient.h"


class DataLayer : public QObject
{
    Q_OBJECT
public:
    explicit DataLayer(QQmlContext* cont, QObject *parent = 0);

    Q_INVOKABLE void loadFromFile();
    Q_INVOKABLE void loadFromClient();

    Q_INVOKABLE void setUsername(QString User);
    Q_INVOKABLE void setPassword(QString Pass);

    QList<QObject*>* getDataModel();

signals:

public slots:
    void setDataModel(QList<QObject*> Data);
    void saveSession(QString Session);

    void authenticate();
private:
    bool saveToFile();

    StineClient     _webClient{};
    QList<QObject*> _dataModel;
    QQmlContext*    _context;

    QString         _username;
    QString         _password;
    QString         _session;

    const std::string _filename{"data"};

};

#endif // DATALAYER_H
