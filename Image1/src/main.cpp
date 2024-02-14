#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ClusterProxy.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include "Detect.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <sys/types.h>

using namespace v1_0::commonapi;

int main(int argc, char *argv[]) {
    Detect detect;
    detect.startCamera();
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;

//    qmlRegisterType<Detect>("com.seame.Detect", 1, 0, "Detect");

//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    return app.exec();
    return 0;
}