#include "ijsondeserialize.h"
#include "enviromentaldata.h"

IJsonDeserialize::IJsonDeserialize(QObject *parent)
    : QObject(parent)
{
    m_environmentalData = new EnviromentalData(m_jsonObj, this);
}

void IJsonDeserialize::FromJson(QString &str)
{
     QJsonParseError jsonError;
    m_document = QJsonDocument::fromJson(str.toLocal8Bit() ,&jsonError);

    if(jsonError.error != QJsonParseError::NoError)
        qDebug() << "Json failed: " << jsonError.errorString();
    else
    {
        m_jsonObj = CreateJsonObj();
        m_environmentalData->update();
    }

}

QJsonObject IJsonDeserialize::CreateJsonObj()
{
    QJsonObject rootObj = m_document.object();
    QJsonObject obj = rootObj["ESPData"].toObject();
    return obj;
}

EnviromentalData *IJsonDeserialize::GetEnvData()
{
    return m_environmentalData;
}



