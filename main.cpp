#include "main.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

void MyClass::cppSlot(const QString& msg) {
    qDebug() << "Called the C++ slot with value:" << msg;

    QVariant rmsg = "Hello from C++";
    QMetaObject::invokeMethod(&m_rootObject, "myQmlFunction",
            Q_ARG(QVariant, rmsg));
}

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    auto it = engine.rootObjects().first();
    MyClass myClass(*it);
    QObject::connect(it, SIGNAL(qmlSignal(QString)), &myClass, SLOT(cppSlot(QString)));

    return app.exec();
}
