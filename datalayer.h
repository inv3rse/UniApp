#ifndef DATALAYER_H
#define DATALAYER_H

#include <QObject>
#include <QString>
#include <QQmlContext>
#include <QFile>

#include "day.h"
#include "stineclient.h"

/**
 * @brief Die Klasse DataLayer handelt das laden, speichern und Updaten der Daten
 */
class DataLayer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isPending READ isPending WRITE setPending NOTIFY pendingChanged)
    Q_PROPERTY(bool authRequired READ authRequired NOTIFY authRequiredChanged)
    Q_PROPERTY(QList<QObject*> dataModel READ getDataModel NOTIFY dataModelChanged)
public:
    explicit DataLayer(QQmlContext* cont, QObject *parent = 0);

    Q_INVOKABLE QString getUsername();
    Q_INVOKABLE void loadDataFromFile();
    Q_INVOKABLE void loadDataFromClient(int day = 0);
    Q_INVOKABLE void setUserAndPassword(QString username, QString password, bool save = false);
    Q_INVOKABLE void abortLogin();

    QList<QObject *> getDataModel();

    bool             isPending();
    bool             authRequired();
    void             setPending(bool Pending);

signals:
    void             pendingChanged();
    void             dataModelChanged();
    void             authRequiredChanged();

public slots:

    /**
     * @brief übernimmt und Speichert die übergebenen Daten
     * @param Data
     */
    void setDataModel(Day* currentDay);

private slots:
    void authenticationRequired();

private:
    bool saveDataToFile();

    StineClient     _webClient{};
    Day*            _currentDay;
    QList<QObject*> _dataModel;
    QQmlContext*    _context;

    bool            _authRequired;
    bool            _isPending;

    static const QString _USERFILE;
    static const QString _DATAFILE;
};

#endif // DATALAYER_H
