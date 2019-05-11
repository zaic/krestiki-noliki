#include "main.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

void MyClass::cppSlot(const int row, const int col) {
    qDebug() << "Called the C++ slot with value:" << row << col;

    if (row < 0 || row > 2 || col < 0 || col > 2) return ;
    if (m_cells[row][col] != CellState::Empty) return ;

    m_cells[row][col] = m_nextTurnState;
    m_nextTurnState = static_cast<CellState>(3 - static_cast<int>(m_nextTurnState));


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
    QObject::connect(it, SIGNAL(tapOnCell(int, int)), &myClass, SLOT(cppSlot(int, int)));

    return app.exec();
}
