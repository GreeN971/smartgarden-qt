#include "enviromentaldata.h"

EnviromentalData::EnviromentalData(QObject *parent)
    : QObject{parent}
    , m_data(new Data(this))
{

}

void EnviromentalData::SetJson(QJsonObject json)
{
    if(json != m_json)
    {
        m_json = json;
        //qDebug() << m_json.size();
    }
}

QJsonObject EnviromentalData::FilterOutValveStatuses(QJsonObject json)
{
    m_valveStatuses.clear();
    const QJsonArray &arr = json.value("valveStatuses").toArray();
    for(const QJsonValue &valveStatus : arr)
    {
        QJsonObject obj = valveStatus.toObject();
        ValveID vID;
        vID.id = obj.value("id").toInt();
        vID.value = obj.value("status").toBool();
        m_valveStatuses.emplace_back(vID);
    }

    json.remove("valveStatuses");

    FromJson(json);

    return json;
}

void EnviromentalData::FromJson(QJsonObject json)
{
    m_data->FromJson(json);
}
/*
Data &EnviromentalData::getData()
{
    return *m_data;
}*/






