/*
    Auteur : Max Bleriot Mba Fossi - 2417938 : Roosevelt Sonfack Ngoune - 2464064
    Date : 04/21/2026
    Cr�� le : 04/08/2026
*/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Echiquier.hpp"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    controlleur::Echiquier* echiquier = new controlleur::Echiquier(&app);
    engine.rootContext()->setContextProperty("echiquier", echiquier);

    engine.loadFromModule("Chess", "Main");
   
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
