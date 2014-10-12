#include "qtquick2controlsapplicationviewer.h"
#include "datalayer.h"
#include "log.h"

#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("1nv3rs3");
    QCoreApplication::setOrganizationDomain("http://1nv3rs3.com/");
    QCoreApplication::setApplicationName("Uni Client");

    Application app(argc, argv);
    QQmlApplicationEngine viewer;

    DataLayer data{viewer.rootContext(),0};

    viewer.rootContext()->setContextProperty("DataLayer",&data);
    viewer.rootContext()->setContextProperty("log",&Log::getInstance());
    viewer.load(QUrl("qrc:/qml/UniApp/main.qml"));



//    viewer.load(QStringLiteral("qml/UniApp/main.qml"));

//    QtQuick2ControlsApplicationViewer viewer;

//    viewer.setMainQmlFile(QStringLiteral("qml/UniApp/main.qml"));
//    viewer.show();

    return app.exec();
}
