#include "Context.h"
#include "enviromentaldata.h"
#include "QFile"

Context::Context(QObject *parent)
    : QObject(parent)
{
    m_environmentalData = new EnviromentalData(m_jsonObj, this);
}

void Context::FromJson(QString &str)
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

std::string Context::Configure()
{
    QJsonParseError jsonError;
    QFile file("configure.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw ConfigureFileErr("configure.json file not found");
    QByteArray qArr = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(qArr, &jsonError);
    if(jsonError.error != QJsonParseError::NoError)
        throw ConfigureFileErr("configure.json file parse failed");

    QJsonObject rootObject = doc.object();
    if (!rootObject.contains("IPAddress"))
        throw ConfigureFileErr("configure.json missing IPAddress parameter");
    QJsonObject obj = rootObject["IPAddress"].toObject();
    std::string address = rootObject.value("time").toVariant().toString().toStdString();
    return address;
}

ConfigureFileErr::ConfigureFileErr(std::string_view str)
    : std::runtime_error(str.data())
{

}

QJsonObject Context::CreateJsonObj()
{
    QJsonObject rootObj = m_document.object();
    QJsonObject obj = rootObj["ESPData"].toObject();
    return obj;
}

EnviromentalData *Context::GetEnvData()
{
    return m_environmentalData;
}



