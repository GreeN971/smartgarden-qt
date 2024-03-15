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
#include "httpclient.h"

#define CONTENT_TYPE "Content-Type"
#define CONTENT_TYPE_JSON "application/json"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //register type for syntax highlighting in QML
    qmlRegisterType<Data>("SmartGarden", 1, 0, "Data");
    qmlRegisterType<EnviromentalData>("SmartGarden", 1, 0, "EnviromentalData");
    qmlRegisterType<SoilIDListModel>("SmartGarden", 1, 0, "SoilIDListModel");
    qmlRegisterType<ValveIDListModel>("SmartGarden", 1, 0, "ValveIDListModel");
    QQmlApplicationEngine engine;

    //IJsonDeserialize will be destroyed after engine destruction
    IJsonDeserialize *test = new IJsonDeserialize(&engine);
    test->CreateQDocument();

    HTTPClient client;
    HTTPClientRequest req;
    req.uri = "http://reqres.in/api/users?page=2";
    req.reqType = httpVerb::GET;
    auto resp = client.Send(req);
    qDebug() << reinterpret_cast<const char*>(resp.data.data());
    qDebug() << resp.status;

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

    return app.exec();
}
