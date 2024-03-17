#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QJsonObject>
#include <QVector>
#include <QString>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QList>
#include <QDebug>
#include <QThread>
#include "SoilID.h"
#include "soilidlistmodel.h"

struct ErrorList
{
    std::string name;
    QString status;
};

class Data : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int temperature MEMBER m_tempeture NOTIFY tempetureChanged);
    Q_PROPERTY(int airHumidity MEMBER m_airHumidity NOTIFY AirHumidityChanged)
    Q_PROPERTY(SoilIDListModel *soilIDListModel MEMBER m_model NOTIFY soilMoisturesChanged)
    QThread workerThread;
public:
    explicit Data(QObject *parent = nullptr);
    virtual ~Data();
    Data &operator=(const Data&);
    //Q_INVOKABLE SoilIDListModel &getModel();

    void SetTempeture(int temepture);
    void SetAirHumidity(int humidity);
    void SetSoilMoistures();
    void FromJson(QJsonObject json);

    int GetTempeture(int tempeture);
    int GetAirHumidity();
    std::vector<short int> GetSoilMoistures();

protected:
    bool ValidateJsonObjects();

signals:
    void DataCheckResult();
    void tempetureChanged();
    void AirHumidityChanged();
    void soilMoisturesChanged();

private:
    int m_tempeture;
    int m_airHumidity;
    QList<SoilID> m_soilData;
    QJsonObject m_filteredJson;
    ErrorList m_errList;
    SoilIDListModel *m_model;
};

#endif // DATA_H
