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

    Q_PROPERTY(bool reloadActive READ reloadActive WRITE waitForReload NOTIFY reloadStateChanged)
public:
    explicit DataLayer(QQmlContext* cont, QObject *parent = 0);

    Q_INVOKABLE void loadUserFromFile();
    Q_INVOKABLE void loadDataFromFile();
    Q_INVOKABLE void loadDataFromClient(int day = 0);
    Q_INVOKABLE void setUsername(QString User);
    Q_INVOKABLE void setPassword(QString Pass);

    QList<QObject *> getDataModel();

    bool             reloadActive();
    void             waitForReload(bool keepWaiting);

signals:

    void             reloadStateChanged();
public slots:

    /**
     * @brief übernimmt und Speichert die übergebenen Daten
     * @param Data
     */
    void setDataModel(Day* currentDay);

    /**
     * @brief Speichert die aktuelle Session in der Datei
     * @param Session
     */
    void saveSession(QString Session);

    /**
     * @brief Setzt Benutzername und Passwort zum Einloggen wenn benötigt
     */
    void authenticate();

    /**
     * @brief Reagiert auf fehlerhaften login Versuch
     */
    void loginFailed();

private:
    bool saveUserToFile();
    bool saveDataToFile();

    StineClient     _webClient{};
    Day*            _currentDay;
    QList<QObject*> _dataModel;
    QQmlContext*    _context;

    QString         _username;
    QString         _password;
    QString         _session;

    static const QString _USERFILE;
    static const QString _DATAFILE;
};

#endif // DATALAYER_H
