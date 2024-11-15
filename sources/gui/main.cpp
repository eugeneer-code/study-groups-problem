#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "Core.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("CommonProjects");
    app.setApplicationName("StudyGroups");

    Core core;

    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Basic");

    engine.rootContext()->setContextProperty("core", &core);

    const QUrl url("qrc:/qml/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
