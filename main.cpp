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
#include <Context.h>
#include <QQmlContext>
#include <QTimer>
#include <io.h>
#include "enviromentaldata.h"
#include "provider.h"

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
    engine.addImportPath("qrc:/");

    
    //Context will be destroyed after engine destruction
    Context *desJson = new Context(&engine);
    //test->FromJson(pro.GetData());

    QTimer *timer = new QTimer(&engine);
    timer->connect(timer, &QTimer::timeout, [desJson, &app]
    {
        try
        {
            Provider provider(desJson->Configure());
            desJson->FromJson(provider.GetData());
        }
        catch(const ConfigureFileErr &e)
        {
            QFile file("log.txt");
            file.open(QFile::Append);
            file.write(e.what());
            file.write("\n");
            file.close();
            app.exit(-1);
        }
        catch (const std::runtime_error &e)
        {
            qDebug() << e.what();
        }
    });
    timer->setInterval(5000);

    //{"http://192.168.11.28/espdata"};

    const QUrl url(u"qrc:/qml/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        [](const QUrl &url) {
            QFile file("log.txt");
            file.open(QFile::Append);
            file.write("failed to load QML");
            file.write("\n");
            file.close();
            QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    timer->start();
    //make object instance visible in QML
    engine.rootContext()->setContextProperty("envData", desJson->GetEnvData());
    engine.load(url);


    return app.exec();
}
