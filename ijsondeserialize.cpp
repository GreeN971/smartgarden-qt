#include "ijsondeserialize.h"
#include "enviromentaldata.h"

IJsonDeserialize::IJsonDeserialize(QObject *parent)
    : QObject(parent)
    , m_document{CreateQDocument()}
    , m_jsonObj {CreateJsonObj()}
{
    m_environmentalData = new EnviromentalData(this);
    m_environmentalData->SetJson(m_jsonObj);
    m_environmentalData->FilterOutValveStatuses(m_jsonObj);
}

QByteArray IJsonDeserialize::ReadDocument()
{
    QFile file(":Resources/resource.json");
    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    file.close();

    return bytes;
}

QJsonDocument IJsonDeserialize::CreateQDocument()
{
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(ReadDocument(), &jsonError);

    if(jsonError.error != QJsonParseError::NoError)
        qDebug() << "Json failed: " << jsonError.errorString().toStdU32String();
    return jsonDoc;
}

QJsonObject IJsonDeserialize::CreateJsonObj()
{
    QJsonObject rootObj = m_document.object();
    QJsonObject obj = rootObj["ESPData"].toObject();
    return obj;
}

void IJsonDeserialize::ReadJson()
{
    //qDebug() <<  m_jsonObj;
}

EnviromentalData *IJsonDeserialize::GetEnvData()
{
    return m_environmentalData;
}



