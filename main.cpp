#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QQmlContext>
#include "qtbridge/MonitorController.h"
#include "qtbridge/ProcessModel.h"
#include "qtbridge/EnergyController.h"
#include "qtbridge/EnergyController.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MonitorController controller;
    engine.rootContext()->setContextProperty("backend", &controller);

    ProcessModel processModel;
    engine.rootContext()->setContextProperty("processModel", &processModel);

    EnergyController energyController;
    engine.rootContext()->setContextProperty("energyBackend", &energyController);

    const QUrl url(QStringLiteral("qrc:/qt/qml/MyApp/Main.qml"));
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

