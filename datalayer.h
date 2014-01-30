#ifndef DATALAYER_H
#define DATALAYER_H

#include <QObject>
#include <QString>
#include <string>
#include <QQmlContext>
#include <QFile>
#include <fstream>
#include "stineclient.h"


class DataLayer : public QObject
{
    Q_OBJECT
public:
    explicit DataLayer(QQmlContext* cont, QObject *parent = 0);

    Q_INVOKABLE void loadUserFromFile();
    Q_INVOKABLE void loadDataFromFile();
    Q_INVOKABLE void loadDataFromClient();

    Q_INVOKABLE void setUsername(QString User);
    Q_INVOKABLE void setPassword(QString Pass);

    QList<QObject*> getDataModel();

signals:

public slots:
    void setDataModel(QList<QObject*> Data);
    void saveSession(QString Session);

    void authenticate();
    void loginFailed();
private:
    bool saveUserToFile();
    bool saveDataToFile();

    StineClient     _webClient{};
    QList<QObject*> _dataModel;
    QQmlContext*    _context;

    QString         _username;
    QString         _password;
    QString         _session;

    static const std::string _USERFILE;
    static const std::string _DATAFILE;
};

#endif // DATALAYER_H
