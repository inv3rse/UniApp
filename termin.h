#ifndef TERMIN_H
#define TERMIN_H

#include <QObject>
#include <QString>

class Termin : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString Description READ getDescription WRITE setDescription NOTIFY DescriptionChanged)
    Q_PROPERTY(QString Time READ getTime WRITE setTime NOTIFY TimeChanged)
    Q_PROPERTY(QString Place READ getPlace WRITE setPlace NOTIFY PlaceChanged)
    Q_PROPERTY(QString InfoLink READ getInfoLink WRITE setInfoLink NOTIFY InfoLinkChanged)
public:
    explicit Termin(QString desc, QString time,QString place,QString link, QObject *parent = 0);
    explicit Termin(QObject *parent = 0);

    Termin(const Termin& other);

    void setDescription(const QString & desc);
    void setTime(const QString & time);
    void setPlace(const QString & place);
    void setInfoLink(const QString & link);

    QString getDescription();
    QString getTime();
    QString getPlace();
    QString getInfoLink();

signals:
    void DescriptionChanged();
    void TimeChanged();
    void PlaceChanged();
    void InfoLinkChanged();

public slots:

private:
    QString _description;
    QString _time;
    QString _place;
    QString _infoLink;
};

#endif // STINEDATA_H
