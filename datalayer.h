#ifndef DATALAYER_H
#define DATALAYER_H

#include <QObject>
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

    QList<QObject*> getDataModel();

signals:

public slots:
    void setDataModel(QList<QObject*> Data);

private:
    bool saveToFile();

    StineClient     _webClient;
    QList<QObject*> _dataModel;
    QQmlContext*    _context;

};

#endif // DATALAYER_H
