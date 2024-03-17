#ifndef ENVIROMENTALDATA_H
#define ENVIROMENTALDATA_H

#include "data.h"
#include "ValveID.h"
#include "valveidlistmodel.h"
#include <QObject>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QQmlContext>
#include <QQmlApplicationEngine>

class EnviromentalData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ValveIDListModel *valveIDListModel
                   MEMBER m_model NOTIFY valveStatusesChanged)
    Q_PROPERTY(Data *data MEMBER m_data NOTIFY dataChanged)
public:
    explicit EnviromentalData(QJsonObject &obj,QObject *parent = nullptr);
    // Q_INVOKABLE - flag that allows to call function in QML

    QJsonObject FilterOutValveStatuses(QJsonObject json);
    void FromJson(QJsonObject json);


signals:
    void dataChanged();
    void valveStatusesChanged();
    void jsonChanged();
public slots:
    void update();
private:
    QJsonObject &m_json;
    Data *m_data;
    QList<ValveID> m_valveStatuses;
    ValveIDListModel *m_model;
};

#endif // ENVIROMENTALDATA_H
//Add check for values actualy being changed
//via NOTIFY, since sending singal when nothing
//has changed is waste of resources
//Later on impelement look up table that has all the
//valves and their values.
