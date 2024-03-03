#ifndef ENVIROMENTALDATA_H
#define ENVIROMENTALDATA_H

#include "data.h"
#include <QObject>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QQmlContext>
#include <QQmlApplicationEngine>

struct ValveID {
    int id;
    bool value;
};

class EnviromentalData : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QJsonObject jsonObject MEMBER
     //              m_json NOTIFY SendJson)
    /*Q_PROPERTY(std::vector<ValveID> valveStatuses
                   MEMBER m_valveStatuses NOTIFY UpdateValveStatuses)*/

    Q_PROPERTY(Data *data MEMBER m_data NOTIFY dataChanged)
public:
    explicit EnviromentalData(QObject *parent = nullptr);
    // Q_INVOKABLE - flag that allows to call function in QML
    void SetJson(QJsonObject json);
    QJsonObject FilterOutValveStatuses(QJsonObject json);
    void FromJson(QJsonObject json);
    //Data &getData();

signals:
    void dataChanged();
private:
    QJsonObject m_json;
    Data *m_data;
    std::vector<ValveID> m_valveStatuses;
};

#endif // ENVIROMENTALDATA_H
//Add check for values actualy being changed
//via NOTIFY, since sending singal when nothing
//has changed is waste of resources
//Later on impelement look up table that has all the
//valves and their values.
