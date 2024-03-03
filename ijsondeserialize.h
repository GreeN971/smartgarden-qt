#ifndef IJSONDESERIALIZE_H
#define IJSONDESERIALIZE_H
#include "enviromentaldata.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QResource>
#include <QObject>

class IJsonDeserialize : public QObject
{
public:
    IJsonDeserialize(QObject *obj = nullptr);
    IJsonDeserialize(QJsonObject obj);
    QByteArray ReadDocument();
    QJsonDocument CreateQDocument();
    QJsonObject CreateJsonObj();
    void ReadJson();

    EnviromentalData *GetEnvData();

private:
    EnviromentalData *m_environmentalData;
    QJsonDocument m_document;
    QJsonObject m_jsonObj;
};

#endif // IJSONDESERIALIZE_H
