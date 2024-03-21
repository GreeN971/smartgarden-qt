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

class Context : public QObject
{
public:
    Context(QObject *obj = nullptr);
    Context(QJsonObject obj);
    //void ReadDocument(char *data);
    QJsonDocument CreateQDocument();
    QJsonObject CreateJsonObj();
    void FromJson(QString &str);

    EnviromentalData *GetEnvData();

private:
    EnviromentalData *m_environmentalData;
    QJsonDocument m_document;
    QJsonObject m_jsonObj;
};

#endif // IJSONDESERIALIZE_H
