#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QResource>
#include <ijsondeserialize.h>
#include <QQmlContext>
#include "enviromentaldata.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //register type for syntax highlighting in QML
    qmlRegisterType<Data>("SmartGarden", 1, 0, "Data");
    qmlRegisterType<EnviromentalData>("SmartGarden", 1, 0, "EnviromentalData");
    qmlRegisterType<SoilIDListModel>("SmartGarden", 1, 0, "SoilIDListModel");
    QQmlApplicationEngine engine;

    //IJsonDeserialize will be destoyed after engine destruction
    IJsonDeserialize *test = new IJsonDeserialize(&engine);
    test->CreateQDocument();

    const QUrl url(u"qrc:/SmartGardenV2/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    //make object instance visible in QML
    engine.rootContext()->setContextProperty("envData", test->GetEnvData());
    engine.load(url);

    /*
    QFile file(":Resources/resource.json");
    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes, &jsonError);

    if(jsonError.error != QJsonParseError::NoError)
        qDebug() << "Json failed: " << jsonError.errorString().toStdU32String();

    QJsonObject rootObj = jsonDoc.object();
    qDebug() << rootObj;
    QJsonObject dataObj = rootObj["ESPData"].toObject();

    int temp = dataObj.value("tempeture").toInt();
    int airHum = dataObj.value("airHumidity").toInt();
    int soilMoistureOne = dataObj.value("soilMoistureOne").toInt();
    int soilMoistureTwo = dataObj.value("soilMoistureTwo").toInt();

        //for(int i = 0; i < dataRoot.size(); i++
    qDebug() << "Temp is - " << airHum << soilMoistureOne;

    */



    return app.exec();
}
