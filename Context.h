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
#include <string_view>

class ConfigureFileErr : public std::runtime_error
{
public:
    ConfigureFileErr(std::string_view str);
};

class Context : public QObject
{
public:
    Context(QObject *obj = nullptr);
    Context(QJsonObject obj);
    //void ReadDocument(char *data);
    QJsonDocument CreateQDocument();
    QJsonObject CreateJsonObj();
    void FromJson(QString &str);
    std::string Configure();

    EnviromentalData *GetEnvData();

private:
    EnviromentalData *m_environmentalData;
    QJsonDocument m_document;
    QJsonObject m_jsonObj;
};

#endif // IJSONDESERIALIZE_H
