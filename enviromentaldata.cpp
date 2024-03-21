#include "enviromentaldata.h"

EnviromentalData::EnviromentalData(QJsonObject &obj, QObject *parent)
    : QObject{parent}
    , m_json(obj)
    , m_data(new Data(this))
    , m_model(new ValveIDListModel(m_valveStatuses, this))
{
    connect(this, &EnviromentalData::jsonChanged, this, &EnviromentalData::update);
}

void EnviromentalData::update()
{
    FilterOutValveStatuses(m_json);
}

QJsonObject EnviromentalData::FilterOutValveStatuses(QJsonObject json)
{
    m_model->layoutAboutToBeChanged();
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

    emit valveStatusesChanged();

    json.remove("valveStatuses");
    FromJson(json);

    m_model->layoutChanged();
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






