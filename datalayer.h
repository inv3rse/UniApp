#ifndef DATALAYER_H
#define DATALAYER_H

#include <QObject>
#include <QString>
#include <QQmlContext>
#include <vector>
#include <fstream>
#include "stineclient.h"


class DataLayer : public QObject
{
    Q_OBJECT
public:
    explicit DataLayer(QQmlContext* cont, QObject *parent = 0);

    void loadFromFile();
    void loadFromClient();

    void setUsername(QString User);
    void setPassword(QString Pass);

    QList<QObject*>* getDataModel();

signals:

public slots:
    void setDataModel(QList<QObject*> Data);
    void saveSession(QString Session);

private:
    bool saveToFile();

    StineClient     _webClient{};
    QList<QObject*> _dataModel;
    QQmlContext*    _context;

    QString         _username;
    QString         _password;
    QString         _session;

};

#endif // DATALAYER_H
