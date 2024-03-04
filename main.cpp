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
    qmlRegisterType<ValveIDListModel>("SmartGarden", 1, 0, "ValveIDListModel");
    QQmlApplicationEngine engine;

    //IJsonDeserialize will be destroyed after engine destruction
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

    return app.exec();
}
