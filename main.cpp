#include "parsejson.h"
#include "qmlcreator.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QGuiApplication>
#include <QQuickWindow>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    ParseJson file("D:/QT_project/Ronia/configure.json");

    QList<matchmember> field = file.get();

    QMLCreator component(field);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("untitled2", "Main");

    return app.exec();
}
