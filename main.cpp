#include "qtquick2controlsapplicationviewer.h"
#include "stineclient.h"

#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    Application app(argc, argv);
    QQmlApplicationEngine viewer;
    QList<QObject*> dataModel;
    StineClient Client{&dataModel,viewer.rootContext()};


    viewer.rootContext()->setContextProperty("Client",&Client);
    viewer.rootContext()->setContextProperty("dataModel",QVariant::fromValue(dataModel));
    viewer.load(QUrl("qrc:/qml/UniApp/main.qml"));
//    viewer.load(QStringLiteral("qml/UniApp/main.qml"));

//    QtQuick2ControlsApplicationViewer viewer;

//    viewer.setMainQmlFile(QStringLiteral("qml/UniApp/main.qml"));
//    viewer.show();

    return app.exec();
}
