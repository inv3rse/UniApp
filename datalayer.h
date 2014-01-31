#ifndef DATALAYER_H
#define DATALAYER_H

#include <QObject>
#include <QString>
#include <QQmlContext>
#include <QFile>

#include "stineclient.h"

/**
 * @brief Die Klasse DataLayer handelt das laden, speichern und Updaten der Daten
 */
class DataLayer : public QObject
{
    Q_OBJECT
public:
    explicit DataLayer(QQmlContext* cont, QObject *parent = 0);

    /**
      * @brief lädt Benutzerdaten zum Einloggen aus der Datei
      */
    Q_INVOKABLE void loadUserFromFile();

    /**
      * @brief lädt Daten in Form von Terminen aus der Datei
      */
    Q_INVOKABLE void loadDataFromFile();

    /**
      * @brief lädt die aktuellen Daten von Stine herunter
      */
    Q_INVOKABLE void loadDataFromClient();

    /**
      * @brief setzt den Username der zum login verwendet wird
      * @param User Benutzername
      */
    Q_INVOKABLE void setUsername(QString User);

    /**
     * @brief setzt das Passwort das zum login verwendet wird
     * @param Pass
     */
    Q_INVOKABLE void setPassword(QString Pass);

    QList<QObject*> getDataModel();

signals:

public slots:

    /**
     * @brief übernimmt und Speichert die übergebenen Daten
     * @param Data
     */
    void setDataModel(QList<QObject*> Data);

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
    QList<QObject*> _dataModel;
    QQmlContext*    _context;

    QString         _username;
    QString         _password;
    QString         _session;

    static const QString _USERFILE;
    static const QString _DATAFILE;
};

#endif // DATALAYER_H
