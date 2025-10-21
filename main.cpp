#include "parsejson.h"
#include "qmlcreator.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ParseJson file("D:/QT_project/Ronia/configure.json");
    QList<matchmember> field = file.get();


    QMLCreator components;

    components.setMembers(field);


    engine.rootContext()->setContextProperty("QMLCreator",&components);
    engine.load(QUrl::fromLocalFile("D:/QT_project/Ronia/Newfolder/QML-CPP/Main.qml"));

    return app.exec();
}
