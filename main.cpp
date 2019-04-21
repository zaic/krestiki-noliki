#include "main.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    MyClass myClass;
    auto it = engine.rootObjects().first();
    QObject::connect(it, SIGNAL(qmlSignal(QString)), &myClass, SLOT(cppSlot(QString)));

    return app.exec();
}
